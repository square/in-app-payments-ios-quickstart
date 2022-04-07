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

import Foundation

struct Constants {
    struct ApplePay {
        static let MERCHANT_IDENTIFIER: String = "REPLACE_ME"
        static let COUNTRY_CODE: String = "US"
        static let CURRENCY_CODE: String = "USD"
    }

    struct Square {
        static let SQUARE_LOCATION_ID: String = "REPLACE_ME"
        static let APPLICATION_ID: String  = "REPLACE_ME"
        static let CHARGE_SERVER_HOST: String = "REPLACE_ME"
        static let CHARGE_URL: String = "\(CHARGE_SERVER_HOST)/chargeForCookie"
    }
}
