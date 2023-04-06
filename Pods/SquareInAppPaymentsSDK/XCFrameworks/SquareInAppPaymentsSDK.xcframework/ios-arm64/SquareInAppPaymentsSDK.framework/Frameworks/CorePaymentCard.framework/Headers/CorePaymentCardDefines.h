//
//  CorePaymentCardDefines.h
//  CorePaymentCard
//
//  Created by Matthias Plappert on 1/23/13.
//  Copyright (c) 2013 Square, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, CPCCardBrandStyle) {
    CPCCardBrandStyleDefault = 0,
    CPCCardBrandStyleEtched,
    CPCCardBrandStyleDisabled,
    CPCCardBrandStyleBlack,
    CPCCardBrandStyleColorful,
};

typedef NS_ENUM(NSInteger, CPCCardVerificationValueSide) {
    CPCCardVerificationValueSideBack = 0,
    CPCCardVerificationValueSideFront
};

typedef NS_ENUM(NSInteger, CPCCardBrand) {
    CPCCardBrandVisa = 0x0,
    CPCCardBrandMasterCard = 0x1,
    CPCCardBrandDiscover = 0x2,
    CPCCardBrandAmericanExpress = 0x3,
    CPCCardBrandJCB = 0x4,
    CPCCardBrandUnknown = 0x5,
    CPCCardBrandDinersClub = 0x6,
    CPCCardBrandChinaUnionPay = 0x7,
    CPCCardBrandSquareGiftCard = 0x8,
    CPCCardBrandInterac = 0x9,
    CPCCardBrandEftpos = 0xA,
    CPCCardBrandSquareCapitalCard = 0xB,
    CPCCardBrandFelica = 0xC,
    CPCCardBrandCount = 0xD
};

typedef NS_ENUM(NSInteger, CPCIssuingBank) {
    CPCIssuingBankUnknown = 0x0,
    CPCIssuingBankAfterpay = 0x1,
    CPCIssuingBankCashApp = 0x2,
    CPCIssuingBankSquare = 0x3,
};

typedef NS_ENUM(NSInteger, CPCFelicaCardBrand) {
    CPCFelicaCardBrandUnknown = 0,
    CPCFelicaCardBrandCommon,
    CPCFelicaCardBrandQUICPay,
    CPCFelicaCardBrandID,
    CPCFelicaCardBrandSuica,
    CPCFelicaCardBrandRakuten,
    CPCFelicaCardBrandWAON,
    CPCFelicaCardBrandNanaco,
    CPCFelicaCardBrandPiTaPa
};
