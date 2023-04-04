//
//  CPCCardBrandDetection.h
//  CorePaymentCard
//
//  Created by Ken Wigginton on 4/10/15.
//  Copyright (c) 2015 Square, Inc. All rights reserved.
//
//  This code is duplicated from riker's <cardreader_shared/crs_payment.h>
//  It is tested extensively both there and in this library.
//  If you have any changes to make, please do so in both locations.
//  TODO(kenw): RI-8796 DRY up this logic into a tiny submodule.

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "CorePaymentCardDefines.h"

/// Returns Issuer ID code for a pan with minimum of first four digits non-redacted.
CPCCardBrand cpc_payment_get_issuer_for_pan(uint8_t const *number);
