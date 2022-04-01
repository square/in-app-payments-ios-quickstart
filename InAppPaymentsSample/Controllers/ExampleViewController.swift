//
//  Copyright © 2018 Square, Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

import UIKit
import SquareInAppPaymentsSDK

enum Result<T> {
    case success
    case failure(T)
    case canceled
}

class ExampleViewController: UIViewController {
    fileprivate var applePayResult: Result<String> = Result.canceled

    override func loadView() {
        let cookieView = ExampleView()
        self.view = cookieView

        cookieView.buyButton.addTarget(self, action: #selector(didTapBuyButton), for: .touchUpInside)
    }
    
    @objc private func didTapBuyButton() {
        showOrderSheet()
    }
    
    private func showOrderSheet() {
        // Open the buy modal
        let orderViewController = OrderViewController()
        orderViewController.delegate = self
        let nc = OrderNavigationController(rootViewController: orderViewController)
        nc.modalPresentationStyle = .custom
        nc.transitioningDelegate = self
        present(nc, animated: true, completion: nil)
    }
    
    
    private func printCurlCommand(nonce : String) {
        let uuid = UUID().uuidString
        print("curl --request POST https://connect.squareupsandbox.com/v2/payments \\" +
            "--header \"Content-Type: application/json\" \\" +
            "--header \"Authorization: Bearer YOUR_ACCESS_TOKEN\" \\" +
            "--header \"Accept: application/json\" \\" +
            "--data \'{" +
            "\"idempotency_key\": \"\(uuid)\"," +
            "\"autocomplete\": true," +
            "\"amount_money\": {" +
            "\"amount\": 100," +
            "\"currency\": \"USD\"}," +
            "\"source_id\": \"\(nonce)\"" +
            "}\'");
    }
    
    private var serverHostSet: Bool {
        return Constants.Square.CHARGE_SERVER_HOST != "REPLACE_ME"
    }
    
    private var appleMerchanIdSet: Bool {
        return Constants.ApplePay.MERCHANT_IDENTIFIER != "REPLACE_ME"
    }
}

extension ExampleViewController {
    func makeCardEntryViewController() -> SQIPCardEntryViewController {
        // Customize the card payment form
        let theme = SQIPTheme()
        theme.errorColor = .red
        theme.tintColor = Color.primaryAction
        theme.keyboardAppearance = .light
        theme.messageColor = Color.descriptionFont
        theme.saveButtonTitle = "Pay"

        return SQIPCardEntryViewController(theme: theme)
    }
}

extension ExampleViewController: UIViewControllerTransitioningDelegate {
    func presentationController(forPresented presented: UIViewController, presenting: UIViewController?, source: UIViewController) -> UIPresentationController? {
        return HalfSheetPresentationController(presentedViewController: presented, presenting: presenting)
    }
}

// MARK: - OrderViewControllerDelegate functions
extension ExampleViewController: OrderViewControllerDelegate {
    func didRequestPayWithCard() {
        dismiss(animated: true) {
            let vc = self.makeCardEntryViewController()
            vc.delegate = self

            let nc = UINavigationController(rootViewController: vc)
            self.present(nc, animated: true, completion: nil)
        }
    }

    func didRequestPayWithApplyPay() {
        dismiss(animated: true) {
            self.requestApplePayAuthorization()
        }
    }

    private func didNotChargeApplePay(_ error: String) {
        // Let user know that the charge was not successful
        let alert = UIAlertController(title: "Your order was not successful",
                                      message: error,
                                      preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        present(alert, animated: true, completion: nil)
    }
    
    private func didChargeSuccessfully() {
        // Let user know that the charge was successful
        let alert = UIAlertController(title: "Your order was successful",
                                      message: "Go to your Square dashbord to see this order reflected in the sales tab.",
                                      preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        present(alert, animated: true, completion: nil)
    }
    
    private func showCurlInformation() {
        let alert = UIAlertController(title: "Nonce generated but not charged",
                                      message: "Check your console for a CURL command to charge the nonce, or replace Constants.Square.CHARGE_SERVER_HOST with your server host.",
                                      preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        present(alert, animated: true, completion: nil)
    }
    
    private func showMerchantIdNotSet() {
        let alert = UIAlertController(title: "Missing Apple Pay Merchant ID",
                                      message: "To request an Apple Pay nonce, replace Constants.ApplePay.MERCHANT_IDENTIFIER with a Merchant ID.",
                                      preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        present(alert, animated: true, completion: nil)
    }
}

extension ExampleViewController: SQIPCardEntryViewControllerDelegate {
    func cardEntryViewController(_ cardEntryViewController: SQIPCardEntryViewController, didCompleteWith status: SQIPCardEntryCompletionStatus) {
        // Note: If you pushed the card entry form onto an existing navigation controller,
        // use UINavigationController.popViewController(animated:) instead
        dismiss(animated: true) {
            switch status {
            case .canceled:
                self.showOrderSheet()
                break
            case .success:
                guard self.serverHostSet else {
                    self.showCurlInformation()
                    return
                }

                self.didChargeSuccessfully()
            }
        }
    }

    func cardEntryViewController(_ cardEntryViewController: SQIPCardEntryViewController, didObtain cardDetails: SQIPCardDetails, completionHandler: @escaping (Error?) -> Void) {
        print("Payment token (nonce) generated by In-App Payments SDK: \(cardDetails.nonce)")
        
        guard serverHostSet else {
            printCurlCommand(nonce: cardDetails.nonce)
            completionHandler(nil)
            return
        }

        ChargeApi.processPayment(cardDetails.nonce) { (transactionID, errorDescription) in
            guard let errorDescription = errorDescription else {
                // No error occured, we successfully charged
                completionHandler(nil)
                return
            }

            // Pass error description
            let error = NSError(domain: "com.example.supercookie", code: 0, userInfo:[NSLocalizedDescriptionKey : errorDescription])
            completionHandler(error)
        }
    }
}

extension ExampleViewController: PKPaymentAuthorizationViewControllerDelegate {
    func requestApplePayAuthorization() {
        guard SQIPInAppPaymentsSDK.canUseApplePay else {
            return
        }

        guard appleMerchanIdSet else {
            showMerchantIdNotSet()
            return
        }

        let paymentRequest = PKPaymentRequest.squarePaymentRequest(
            merchantIdentifier: Constants.ApplePay.MERCHANT_IDENTIFIER,
            countryCode: Constants.ApplePay.COUNTRY_CODE,
            currencyCode: Constants.ApplePay.CURRENCY_CODE
        )

        paymentRequest.paymentSummaryItems = [
            PKPaymentSummaryItem(label: "Super Cookie", amount: 1.00)
        ]

        let paymentAuthorizationViewController = PKPaymentAuthorizationViewController(paymentRequest: paymentRequest)

        paymentAuthorizationViewController!.delegate = self

        present(paymentAuthorizationViewController!, animated: true, completion: nil)
    }

    func paymentAuthorizationViewController(_ controller: PKPaymentAuthorizationViewController,
                                            didAuthorizePayment payment: PKPayment,
                                            handler completion: @escaping (PKPaymentAuthorizationResult) -> Void){

        // Turn the response into a nonce, if possible
        // Nonce is used to actually charge the card on the server-side
        let nonceRequest = SQIPApplePayNonceRequest(payment: payment)

        nonceRequest.perform { [weak self] cardDetails, error in
            guard let cardDetails = cardDetails else {
                let errors = [error].compactMap { $0 }
                completion(PKPaymentAuthorizationResult(status: .failure, errors: errors))
                return
            }
            
            guard let strongSelf = self else {
                completion(PKPaymentAuthorizationResult(status: .failure, errors: []))
                return
            }
            
            guard strongSelf.serverHostSet else {
                strongSelf.printCurlCommand(nonce: cardDetails.nonce)
                strongSelf.applePayResult = .success
                completion(PKPaymentAuthorizationResult(status: .failure, errors: []))
                return
            }
            
            ChargeApi.processPayment(cardDetails.nonce) { (transactionId, error) in
                if let error = error, !error.isEmpty {
                    strongSelf.applePayResult = Result.failure(error)
                } else {
                    strongSelf.applePayResult = Result.success
                }

                completion(PKPaymentAuthorizationResult(status: .success, errors: nil))
            }
        }
    }

    func paymentAuthorizationViewControllerDidFinish(_ controller: PKPaymentAuthorizationViewController) {
        controller.dismiss(animated: true) {
            switch self.applePayResult {
            case .success:
                guard self.serverHostSet else {
                    self.showCurlInformation()
                    return
                }
                self.didChargeSuccessfully()
            case .failure(let description):
                self.didNotChargeApplePay(description)
                break
            case .canceled:
                self.showOrderSheet()
            }
        }
    }
}
