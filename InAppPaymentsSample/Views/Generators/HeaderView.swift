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

import UIKit

class HeaderView : UIStackView {
    lazy var closeButton = makeCloseButton()
    private var title: String = ""

    init(title: String) {
        super.init(frame: .zero)
        commonInit()
    }

    override init(frame: CGRect) {
        super.init(frame: frame)
        commonInit()
    }

    required init(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        commonInit()
    }

    private func commonInit() {
        distribution = .fillProportionally
        alignment = .center
        layoutMargins = UIEdgeInsets(top: 0, left: 0, bottom: 0, right: 0)
        isLayoutMarginsRelativeArrangement = true
        addArrangedSubview(closeButton)
        addArrangedSubview(makeOrderTitleLabel(text: title))

        let hiddenCloseButton = makeCloseButton()
        hiddenCloseButton.alpha = 0.0
        addArrangedSubview(hiddenCloseButton)
    }
}

extension HeaderView {
    private func makeCloseButton() -> UIButton {
        let button = UIButton(type: .system)
        button.setImage(#imageLiteral(resourceName: "CloseButton"), for: .normal)
        button.translatesAutoresizingMaskIntoConstraints = false
        button.tintColor = Color.descriptionFont

        return button
    }


    private func makeOrderTitleLabel(text: String) -> UILabel {
        let label = UILabel()
        label.text = "Place your order"
        label.textColor = UIColor.black
        label.font = UIFont.systemFont(ofSize: 18, weight: .bold)
        label.textAlignment = .center

        label.translatesAutoresizingMaskIntoConstraints = false

        return label
    }
}
