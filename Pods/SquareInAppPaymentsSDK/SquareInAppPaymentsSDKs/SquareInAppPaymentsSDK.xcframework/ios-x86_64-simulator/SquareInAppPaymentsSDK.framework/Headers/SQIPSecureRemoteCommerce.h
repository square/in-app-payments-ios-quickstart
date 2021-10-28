//
//  SQIPSecureRemoteCommerce.h
//  SquareInAppPaymentsSDK
//
//  Created by Tyten Teegarden on 12/9/20.
//  Copyright © 2020 Square, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SQIPCardDetails.h"
#import "SQIPSecureRemoteCommerceParameters.h"
#import <WebKit/WebKit.h>

/**
 This class starts and handles a Secure Remote Commerce transaction.

 @discussion A strong reference to the object must be maintained.
 */
@interface SQIPSecureRemoteCommerce : NSObject
typedef void (^SQIPSecureRemoteCommerceCompletionHandler)(SQIPCardDetails *_Nullable cardDetails, NSError *_Nullable error);

/**
 Starts the Secure Remote Commerce transaction. Calling this method will modally present the dialogs over the designated view controller.

 @discussion If the request completes successfully the completion handler will pass in card details and no error. If there is an error, the error will be passed without card details. If the action is cancelled both the details and the error will be `nil`.
 
 @param presentingViewController The view controller over whose view the dialogs willappear.
 @param secureRemoteCommerceParameters The necessary parameters for conducting a Secure Remote Commerce Transaction. Currently just the amount in USD.
 @param completionHandler The completion handler to be called upon success or failure of the nonce request.
 */
- (void)createPaymentRequest:(nonnull UIViewController *)presentingViewController
    secureRemoteCommerceParameters:(SQIPSecureRemoteCommerceParameters)secureRemoteCommerceParameters
                 completionHandler:(nonnull SQIPSecureRemoteCommerceCompletionHandler)completionHandler;

@end
