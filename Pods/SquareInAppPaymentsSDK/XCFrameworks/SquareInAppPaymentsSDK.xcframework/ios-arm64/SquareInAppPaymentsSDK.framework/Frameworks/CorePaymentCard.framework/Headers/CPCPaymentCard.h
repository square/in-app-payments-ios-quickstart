//
//  CPCPaymentCard.h
//  CorePaymentCard
//
//  Created by Michael White on 1/8/13.
//  Copyright (c) 2013 Square, Inc. All rights reserved.
//

#import <CorePaymentCard/CorePaymentCardDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, CPCPaymentCardComparisonOptions) {
    CPCPaymentCardComparisonOptionsNone = 0,
    CPCPaymentCardComparisonOptionSoftMatchCUPCards = (1 << 0)
};


typedef NS_ENUM(NSInteger, CPCPaymentCardReaderType) {
    CPCPaymentCardReaderTypeUnknown = 0,
    CPCPaymentCardReaderTypeKeyed,
    CPCPaymentCardReaderTypeUnencrypted,
    CPCPaymentCardReaderTypeO1,
    CPCPaymentCardReaderTypeS1,
    CPCPaymentCardReaderTypeR4,
    CPCPaymentCardReaderTypeR6,
    CPCPaymentCardReaderTypeA10,
    CPCPaymentCardReaderTypeR12,
    CPCPaymentCardReaderTypeR12C,
    CPCPaymentCardReaderTypeS3,
    CPCPaymentCardReaderTypeEmbedded
};


typedef NS_ENUM(NSInteger, CPCPaymentCardEntryMethod) {
    CPCPaymentCardEntryMethodUnknown = 0,
    CPCPaymentCardEntryMethodKeyed,
    CPCPaymentCardEntryMethodSwiped,
    CPCPaymentCardEntryMethodInserted,
    CPCPaymentCardEntryMethodProximity,
};

typedef NS_ENUM(NSInteger, CPCPaymentCardCardholderVerificationMethod) {
    /// The CVM is unknown. An invalid CVM.
    CPCPaymentCardCardholderVerificationMethodUnknown = 0,
    /// The CVM failed to be successfully performed.
    CPCPaymentCardCardholderVerificationMethodFailed,
    /// The CVM is an offline plaintext PIN verified by the chip card.
    CPCPaymentCardCardholderVerificationMethodOfflinePlaintextPIN,
    /// The CVM is an online encrypted PIN verified by the issuer.
    CPCPaymentCardCardholderVerificationMethodOnlineEncipheredPIN,
    /// The CVM is a combination of offline plaintext PIN verified by the chip card and signature.
    CPCPaymentCardCardholderVerificationMethodOfflinePlaintextPINAndSignature,
    /// The CVM is an offline encrypted PIN verified by the chip card.
    CPCPaymentCardCardholderVerificationMethodOfflineEncipheredPIN,
    /// The CVM is a combination of offline encrypted PIN verified by the chip card and signature.
    CPCPaymentCardCardholderVerificationMethodOfflineEncipheredPINAndSignature,
    /// The CVM is performed by the contactless device. (e.g. ApplePay fingerprint or passcode, AndroidPay passcode)
    CPCPaymentCardCardholderVerificationMethodOnDevice,
    /// The CVM is signature.
    CPCPaymentCardCardholderVerificationMethodSignature,
    /// No CVM is required.
    CPCPaymentCardCardholderVerificationMethodNone,
};


typedef NS_ENUM(NSInteger, CPCPaymentCardDisplayStyle) {
    CPCPaymentCardDisplayStyleShort,
    CPCPaymentCardDisplayStyleNormal,
};


FOUNDATION_EXPORT BOOL CPCPaymentCardReaderTypeSupportsChipOrContactless(CPCPaymentCardReaderType readerType) CF_SWIFT_NAME(getter:CPCPaymentCardReaderType.supportsChipOrContactless(self:));
FOUNDATION_EXPORT NSString *NSStringFromCPCPaymentCardEntryMethod(CPCPaymentCardEntryMethod entryMethod) CF_SWIFT_NAME(getter:CPCPaymentCardEntryMethod.description(self:));
FOUNDATION_EXPORT NSString *NSStringFromCPCPaymentCardVerificationMethod(CPCPaymentCardCardholderVerificationMethod method) CF_SWIFT_NAME(getter:CPCPaymentCardCardholderVerificationMethod.description(self:));


@interface CPCPaymentCard : NSObject

/// @name General properties.
@property (nonatomic, copy, readonly, nullable) NSString *number;
@property (nonatomic, copy, readonly, nullable) NSString *numberLastFour;
@property (nonatomic, assign, readonly) CPCCardBrand brand;
@property (nonatomic, assign, readonly) CPCIssuingBank bank;
@property (nonatomic, copy, nullable) NSString *firstName;
@property (nonatomic, copy, nullable) NSString *lastName;
@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, strong, nullable) NSDate *expiration;
@property (nonatomic, copy, nullable) NSString *verificationValue;
@property (nonatomic, copy, nullable) NSString *postalCode;
@property (nonatomic, copy, readonly, nullable) NSString *name;
@property (nonatomic, assign, readonly) CPCPaymentCardReaderType readerType;
@property (nonatomic, assign, readonly) CPCPaymentCardEntryMethod entryMethod;
@property (nonatomic, assign, readonly) CPCPaymentCardCardholderVerificationMethod cardholderVerificationMethod;

/// @name Authorization and Capture request/response data.
@property (nonatomic, copy, nullable) NSData *authorizationRequestData;
@property (nonatomic, copy, nullable) NSData *authorizationRequestKeyData;

@property (nonatomic, copy, nullable) NSData *authorizationResponseData;
@property (nonatomic, copy, nullable) NSData *captureRequestData;

/// @return YES if the card is authorizable where authorizable means an add-tender request is possible to transition the payment source into .Authorizing.
@property (nonatomic, assign, readonly, getter=isAuthorizable) BOOL authorizable;

/// @return YES if the card is capturable where capturable means a complete-bill request is possbile to transition the payment source into .Captured.
@property (nonatomic, assign, readonly, getter=isCapturable) BOOL capturable;

/** When YES, indicates that the card must remain present (e.g. inserted into the reader) until
 after capture request data has been received by the reader. When NO, indicates that the card can be removed after
 auth request data. */
@property (nonatomic, assign) BOOL continuedCardPresenceRequiredAfterAuthRequestUntilCaptureRequest;

/// Return @YES if the card presence is still required, based on the current entry method, auth data state, and capture data state, and underlying support for `continuedCardPresenceRequiredAfterAuthRequestUntilCaptureRequest`.
@property (nonatomic, assign, readonly, getter=isCardPresenceRequiredToCompleteTransaction) BOOL continuedCardPresenceRequiredToCompleteTransaction;

/// @name Presence of valid track data.
@property (nonatomic, assign, readonly) BOOL hasValidTrack1;
@property (nonatomic, assign, readonly) BOOL hasValidTrack2;
@property (nonatomic, assign, readonly) BOOL hasValidTrack3;

/// @name Action types.
@property (nonatomic, assign, readonly) BOOL wasKeyed;
@property (nonatomic, assign, readonly) BOOL wasSwiped;
@property (nonatomic, assign, readonly) BOOL wasInserted;
@property (nonatomic, assign, readonly) BOOL wasInProximity;

/// @name EMV specific

@property (nonatomic, assign, getter=isEMVOfflineApproved) BOOL EMVOfflineApproved;

/// An array of CRPaymentApplications corresponding to all the available applications of an EMV payment card.
@property (nonatomic, copy) NSArray *applications;

/// An array of CRPaymentAccounts corresponding to all the available accounts of an EMV payment card.
@property (nonatomic, copy) NSArray *accounts;

+ (NSDateFormatter *)expirationDateFormatter;

+ (instancetype)paymentCardWithGiftCardPAN:(NSString *)giftCardPAN;
+ (instancetype)paymentCardWithAlphanumericGiftCardPAN:(NSString *)giftCardPAN;

- (instancetype)initWithCardNumber:(NSString *)cardNumber;
- (instancetype)initWithBrand:(CPCCardBrand)brand cardNumberLastFour:(nullable NSString *)numberLastFour;

/**
The card brand is set to Unknown, the last four digits are nil, the reader type is set to <code>readerType</code>, and card entry method set to <code>entryMethod</code>.
*/
- (instancetype)initWithReaderType:(CPCPaymentCardReaderType)readerType entryMethod:(CPCPaymentCardEntryMethod)entryMethod;

- (instancetype)initWithBrand:(CPCCardBrand)brand cardNumberLastFour:(nullable NSString *)numberLastFour readerType:(CPCPaymentCardReaderType)readerType entryMethod:(CPCPaymentCardEntryMethod)entryMethod;

@property (nonatomic, readonly) NSUInteger minimumValidNumberLength;

// Display and formatting.
@property (nonatomic, readonly, nullable) NSString *formattedNumber;
@property (nonatomic, readonly, nullable) NSString *formattedMaskedNumber;
@property (nonatomic, readonly, nullable) NSString *maskedNumber;
@property (nonatomic, readonly, nullable) NSString *expirationMonth;
@property (nonatomic, readonly, nullable) NSString *expirationYear;
@property (nonatomic, readonly, nullable) NSString *localizedBrandAndLastFour;

/// Returns a string like "American Express 1234".
- (nullable NSString *)localizedBrandAndNumberDisplayStringWithStyle:(CPCPaymentCardDisplayStyle)displayStyle;

/// Returns a string like "American Express" (or "AmEx" if using the 'Short' DisplayStyle).
- (NSString *)localizedBrandDisplayStringWithStyle:(CPCPaymentCardDisplayStyle)displayStyle;

// The expected length of this type of card number's CVV.
@property (nonatomic, readonly) NSUInteger validVerificationValueLength;

- (nullable NSDictionary *)authorizeDictionary;
- (nullable NSDictionary *)refundDictionary;
- (nullable NSDictionary *)searchDictionary;

- (BOOL)isValid;

- (BOOL)isEqualBrandAndNumberLastFour:(CPCPaymentCard *)otherCard;
- (BOOL)isEqualBrandAndNumberLastFour:(CPCPaymentCard *)otherCard options:(CPCPaymentCardComparisonOptions)options;

- (void)clearCardData;

@property (nonatomic, readonly) BOOL canUseNameForCustomerIdentification;

- (void)configureAsGiftcard;
- (void)applyGiftcardExpiration;

- (void)populateWithCorePaymentCard:(CPCPaymentCard *)paymentCard;

@end

NS_ASSUME_NONNULL_END
