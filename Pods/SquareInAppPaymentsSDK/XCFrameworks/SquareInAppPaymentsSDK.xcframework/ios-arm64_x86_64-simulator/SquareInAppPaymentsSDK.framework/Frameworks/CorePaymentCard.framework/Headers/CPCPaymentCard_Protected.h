//
//  CPCPaymentCard_Protected.h
//  CorePaymentCard
//
//  Created by Michael White on 1/8/13.
//  Copyright (c) 2013 Square, Inc. All rights reserved.
//

#import <CorePaymentCard/CPCPaymentCard.h>


@class CPCString;


@interface CPCPaymentCard ()

@property (nonatomic, copy, readwrite) NSString *number;
@property (nonatomic, copy, readwrite) CPCString *secureNumber;
@property (nonatomic, copy, readwrite) NSString *numberLastFour;
@property (nonatomic, assign, readwrite) CPCCardBrand brand;
@property (nonatomic, assign, readwrite) CPCIssuingBank bank;
@property (nonatomic, assign, readwrite) CPCPaymentCardReaderType readerType;
@property (nonatomic, assign, readwrite) CPCPaymentCardEntryMethod entryMethod;
@property (nonatomic, assign, readwrite) CPCPaymentCardCardholderVerificationMethod cardholderVerificationMethod;

@property (nonatomic, assign, readwrite) BOOL hasValidTrack1;
@property (nonatomic, assign, readwrite) BOOL hasValidTrack2;
@property (nonatomic, assign, readwrite) BOOL hasValidTrack3;

/** When YES, indicates that the card number may contain letters. Used for cases like alphanumeric gift cards */
@property (nonatomic, assign) BOOL allowsAlphanumericCardNumber;

- (BOOL)setNameComponentsFromName:(NSString *)name;

@end
