#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "NSBundle+CPCAdditions.h"
#import "NSString+CPCAdditions.h"
#import "CorePaymentCard.h"
#import "CorePaymentCardDefines.h"
#import "CPCCardUtility.h"
#import "CPCPaymentCard.h"
#import "CPCPaymentCard_Protected.h"
#import "CPCString.h"

FOUNDATION_EXPORT double CorePaymentCardVersionNumber;
FOUNDATION_EXPORT const unsigned char CorePaymentCardVersionString[];

