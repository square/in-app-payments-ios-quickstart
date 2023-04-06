//
//  NSString+CPCAdditions.h
//  CorePaymentCard
//
//  Created by Michael White on 1/9/13.
//  Copyright (c) 2013 Square, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSString (CPCAdditions)

+ (instancetype)_CPC_stringWithCString:(const char *)cString length:(size_t)length encoding:(NSStringEncoding)encoding;

- (NSString *)CPC_stringByRemovingNonNumericCharacters;

@end
