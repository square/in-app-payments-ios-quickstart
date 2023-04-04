//
//  CPCCardUtility.h
//  CorePaymentCard
//
//  Created by Eric Firestone on 1/30/12.
//  Copyright (c) 2012 Square, Inc. All rights reserved.
//

#import <CorePaymentCard/CorePaymentCardDefines.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif


extern const int CPCCardExpirationLength;
extern const int CPCCardCountryCodeLength;
extern const char *CPCCardTrack1FieldSeparator;
extern const char *CPCCardTrack2FieldSeparator;

extern const unichar CPCCardNumberMaskDigit;
extern const NSUInteger CPCCardNumberUnmaskedDigitLength;

extern const unichar CPCCardNumberDigitGroupSpacer;
extern NSString *CPCCardNumberDigitGroupSpacerString;

extern const NSUInteger CPCCardVerificationValueLengthAmericanExpress;
extern const NSUInteger CPCCardVerificationValueLengthDefault;
extern const NSUInteger CPCCardVerificationValueLengthMaximum;

extern const NSRange CPCCardNumberLengthRangeAmericanExpress;
extern const NSRange CPCCardNumberLengthRangeDinersClub;
extern const NSRange CPCCardNumberLengthRangeChinaUnionPay;
extern const NSRange CPCCardNumberLengthRangeDefault;

// Includes spaces when formatted as groupted digits.
extern const NSUInteger CPCCardNumberLengthFormattedMaximum;


// Brand information.
// All brand functions that take a card number expect the raw, unformatted card number. If necessary, use CPCCardNumberWithoutFormatting() first.
FOUNDATION_EXPORT CPCCardBrand CPCCardBrandWithCardNumber(NSString *cardNumber) CF_SWIFT_NAME(CPCCardBrand.init(cardNumber:));
FOUNDATION_EXPORT NSString *CPCCardBrandStringWithBrand(CPCCardBrand brand, BOOL useAbbreviationIfAvailable) CF_SWIFT_NAME(CPCCardBrand.name(self:useAbbreviationIfAvailable:));

FOUNDATION_EXPORT NSString *CPCFelicaCardBrandStringWithBrand(CPCFelicaCardBrand felicaBrand) CF_SWIFT_NAME(CPCFelicaCardBrand.name(self:));

/// Returns a brand string with maximum length of six characters.
FOUNDATION_EXPORT NSString *CPCCardBrandShortStringWithBrand(CPCCardBrand brand) CF_SWIFT_NAME(getter:CPCCardBrand.shortName(self:));

// Brand tokens are the strings used by the server for the different brands.
FOUNDATION_EXPORT CPCCardBrand CPCCardBrandWithBrandIdentifier(NSString *cardBrandString) CF_SWIFT_NAME(CPCCardBrand.init(identifier:));
FOUNDATION_EXPORT NSString *CPCCardBrandIdentifierWithBrand(CPCCardBrand cardBrand) CF_SWIFT_NAME(getter:CPCCardBrand.identifier(self:));


// CVV information.
FOUNDATION_EXPORT CPCCardVerificationValueSide CPCCardVerificationValueSideWithBrand(CPCCardBrand brand) CF_SWIFT_NAME(getter:CPCCardBrand.verificationValueSide(self:));


// Card number validation.
// All validation and formatting functions expect the raw, unformatted card number. If necessary, use CPCCardNumberWithoutFormatting() first.

FOUNDATION_EXPORT NSUInteger CPCCardMinimumValidLengthForCardNumberWithBrand(CPCCardBrand brand) CF_SWIFT_NAME(getter:CPCCardBrand.minimumValidCardNumberLength(self:));
FOUNDATION_EXPORT NSUInteger CPCCardMinimumValidLengthForCardNumber(NSString *cardNumber);

FOUNDATION_EXPORT NSUInteger CPCCardMaximumValidLengthForCardNumberWithBrand(CPCCardBrand brand) CF_SWIFT_NAME(getter:CPCCardBrand.maximumValidCardNumberLength(self:));
FOUNDATION_EXPORT NSUInteger CPCCardMaximumValidLengthForCardNumber(NSString *cardNumber);

FOUNDATION_EXPORT NSRange CPCCardValidLengthRangeForCardNumberWithBrand(CPCCardBrand brand) CF_SWIFT_NAME(getter:CPCCardBrand.validCardNumberLengthRange(self:));
FOUNDATION_EXPORT NSRange CPCCardValidLengthRangeForCardNumber(NSString *cardNumber);

FOUNDATION_EXPORT BOOL CPCCardIsLengthValidForBrand(NSUInteger length, CPCCardBrand brand) CF_SWIFT_NAME(CPCCardBrand.isValidCardNumberLength(_:self:));
FOUNDATION_EXPORT BOOL CPCCardIsCardNumberValidLength(NSString *cardNumber);

FOUNDATION_EXPORT NSUInteger CPCCardValidLengthForVerificationValueWithCardNumber(NSString *cardNumber);
FOUNDATION_EXPORT NSUInteger CPCCardValidLengthForVerificationValueWithBrand(CPCCardBrand brand) CF_SWIFT_NAME(getter:CPCCardBrand.validLengthForVerificationValue(self:));

FOUNDATION_EXPORT BOOL CPCCardIsValidCardNumber(NSString *cardNumber);
FOUNDATION_EXPORT BOOL CPCStringIsValidLuhnChecksum(NSString *string);

FOUNDATION_EXPORT BOOL CPCCardIsNonISORegisteredPrefix(NSString *cardNumber);
FOUNDATION_EXPORT BOOL CPCCardNumberIsNumeric(NSString *cardNumber);

FOUNDATION_EXPORT BOOL CPCCardBrandIsExemptFromLuhnCheck(CPCCardBrand brand) CF_SWIFT_NAME(getter:CPCCardBrand.isExemptFromLuhnCheck(self:));

// Card Suffix
FOUNDATION_EXPORT NSString *CPCCardSuffixWithCardNumber(NSString *cardNumber, NSUInteger cardSuffixLength);


// Formatting
FOUNDATION_EXPORT NSArray *CPCCardFormattedGroupSizesWithLength(NSUInteger expectedLength);

FOUNDATION_EXPORT NSString *CPCCardFormattedCardNumber(NSString *cardNumber);
FOUNDATION_EXPORT NSString *CPCCardFormattedCardNumberWithLength(NSString *cardNumber, NSUInteger expectedLength);

/// Formats a masked card number using the formatting rules for the given brand.
/// Sample input: ●●●●●●●●●●●●1234 output: ●●●● ●●●● ●●●● 1234
FOUNDATION_EXPORT NSString *CPCCardFormattedMaskedCardNumberWithBrand(NSString *maskedCardNumber, CPCCardBrand brand);
FOUNDATION_EXPORT NSString *CPCCardMaskedCardNumber(NSString *cardNumber, unichar maskDigit, NSUInteger unmaskedDigitLength);
FOUNDATION_EXPORT NSString *CPCCardMaskedCardNumberWithLength(NSString *cardNumber, NSUInteger expectedLength, BOOL maskLastDigit, unichar maskDigit, NSUInteger unmaskedDigitLength);
FOUNDATION_EXPORT NSString *CPCCardMaskedCardNumberWithBrandAndSuffix(CPCCardBrand cardBrand, NSString *cardSuffix, unichar maskDigit, NSUInteger unmaskedDigitLength);

FOUNDATION_EXPORT NSString *CPCCardMaskedVerificationValueWithBrand(CPCCardBrand, unichar maskDigit);


// Helper function.
FOUNDATION_EXPORT NSString *CPCCardNumberWithoutFormatting(NSString *cardNumber);
FOUNDATION_EXPORT NSString *CPCAlphanumericCardNumberWithoutFormatting(NSString *cardNumber);
FOUNDATION_EXPORT NSString *CPCCardNumberWithoutCharactersInSet(NSString *cardNumber, NSCharacterSet *characterSet);
