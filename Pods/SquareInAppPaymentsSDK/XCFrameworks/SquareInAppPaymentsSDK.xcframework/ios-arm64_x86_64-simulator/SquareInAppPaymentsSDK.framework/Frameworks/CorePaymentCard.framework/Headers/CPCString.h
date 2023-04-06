//
//  CPCString.h
//  CorePaymentCard
//
//  Created by Michael White on 1/29/13.
//  Copyright (c) 2013 Square, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface CPCString : NSString

@property (nonatomic, assign, readonly) BOOL hasErasedContents;

- (void)eraseContents;

@end
