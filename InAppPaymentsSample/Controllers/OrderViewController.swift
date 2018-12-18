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

protocol OrderViewControllerDelegate: class {
    func didRequestPayWithApplyPay()
    func didRequestPayWithCard()
}

class OrderViewController : UIViewController {
    weak var delegate: OrderViewControllerDelegate?
    var applePayResponse : String?
    
    override func loadView() {
        let orderView = OrderView()
        self.view = orderView

        orderView.addCardButton.addTarget(self, action: #selector(didTapPayButton), for: .touchUpInside)
        orderView.applePayButton.addTarget(self, action: #selector(didTapApplePayButton), for: .touchUpInside)
        orderView.closeButton.addTarget(self, action: #selector(didTapCloseButton), for: .touchUpInside)
    }

    // MARK: - Button tap functions
    
    @objc private func didTapCloseButton() {
        dismiss(animated: true, completion: nil)
    }
    
    @objc private func didTapPayButton() {
        delegate?.didRequestPayWithCard()
    }
    
    @objc private func didTapApplePayButton() {
        delegate?.didRequestPayWithApplyPay()
    }
}

extension OrderViewController: HalfSheetPresentationControllerHeightProtocol {
    var halfsheetHeight: CGFloat {
        return (view as! OrderView).stackView.systemLayoutSizeFitting(UILayoutFittingExpandedSize).height
    }
}
