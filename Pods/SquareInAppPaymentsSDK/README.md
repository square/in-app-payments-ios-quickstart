[![Cocoapods](https://img.shields.io/cocoapods/v/SquareInAppPaymentsSDK)](https://github.com/CocoaPods/CocoaPods)
[![Carthage compatible](https://img.shields.io/badge/Carthage-compatible-4BC51D.svg?style=flat)](https://github.com/Carthage/Carthage)

# Square In-App Payments iOS SDK

Build remarkable payments experiences in your own apps with Square’s [In-App Payments SDK](https://docs.connect.squareup.com/payments/in-app-payments-sdk/what-it-does). Use our pre-built UI to collect sensitive credit card details from your customers, while matching the look and feel of your app. Square takes care of all the complexity of payments - security, risk, and PCI compliance are managed for you, so that you can focus on building the rest of your application.

You can also pair our Square In-App Payments SDK with Square’s [Online Payments APIs](https://squareup.com/developers/online-payment-apis) and [Reader SDK](https://squareup.com/developers/reader-sdk) to accept payments across all channels - online, in-person and in-app - while keeping your back office reporting unified in a single system.

## Installation

### SPM

[Swift Package Manager](https://www.swift.org/package-manager/) support is available for Swift 5.3 and above. Simply add the following to your top-level `dependencies` block within your `Package.swift`:

```swift
dependencies: [
    .package(url: "https://github.com/square/in-app-payments-ios", .upToNextMajor(from: "1.6.0")),
]
```

### Cocoapods

Install with [CocoaPods](http://cocoapods.org/) by adding the following to your Podfile:

```ruby
use_frameworks!

pod "SquareInAppPaymentsSDK"
```

### Carthage

Install with [Carthage](https://github.com/Carthage/Carthage) by adding the following to your Cartfile:

```
github "square/in-app-payments-ios"
```

### Getting Started

For more information and setup instructions, please visit the [Square In-App Payments iOS SDK page](https://docs.connect.squareup.com/payments/in-app-payments-sdk/build-on-ios).
