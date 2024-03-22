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

class ExampleView : UIView {
    lazy var buyButton = ActionButton(backgroundColor: Color.primaryAction, title: "Buy", image: nil)

    override init(frame: CGRect) {
        super.init(frame: frame)
        commonInit()
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        commonInit()
    }
    
    private func commonInit() {
        backgroundColor = Color.background

        setConstraints()
    }
    
    private func setConstraints() {
        let containerStackView = UIStackView()
        containerStackView.translatesAutoresizingMaskIntoConstraints = false
        containerStackView.axis = .vertical
        addSubview(containerStackView)

        let descriptionStackView = UIStackView()
        descriptionStackView.translatesAutoresizingMaskIntoConstraints = false
        descriptionStackView.spacing = 20
        descriptionStackView.axis = .vertical

        NSLayoutConstraint.activate([
            containerStackView.centerXAnchor.constraint(equalTo: self.centerXAnchor),
            containerStackView.centerYAnchor.constraint(equalTo: self.centerYAnchor),
        ])

        containerStackView.addArrangedSubview(makeCookieImage())
        containerStackView.addArrangedSubview(descriptionStackView)

        descriptionStackView.addArrangedSubview(makeTitleLabel())
        descriptionStackView.addArrangedSubview(makeDescriptionLabel())
        descriptionStackView.addArrangedSubview(buyButton)
    }
}

extension ExampleView {
    private func makeCookieImage() -> UIImageView {
        let imageView = UIImageView(image: #imageLiteral(resourceName: "CookieImage"))


        return imageView
    }

    private func makeTitleLabel() -> UILabel {
        let label = UILabel()
        label.textColor = .white
        label.font = UIFont.systemFont(ofSize: 28, weight: .bold)
        label.text = "Super Cookie"
        label.translatesAutoresizingMaskIntoConstraints = false
        label.textAlignment = .center

        return label
    }

    private func makeDescriptionLabel() -> UILabel {
        let textLabel = UILabel()
        textLabel.textColor = .white
        textLabel.font = UIFont.systemFont(ofSize: 16, weight: .regular)
        textLabel.numberOfLines = 2

        let paragraphStyle = NSMutableParagraphStyle()
        paragraphStyle.lineSpacing = 5
        let attributes = [NSAttributedString.Key.paragraphStyle : paragraphStyle]
        textLabel.textAlignment = .right
        textLabel.attributedText = NSMutableAttributedString(string: "Instantly gain special powers\nwhen ordering a super cookie", attributes: attributes)
        textLabel.textAlignment = .center

        textLabel.translatesAutoresizingMaskIntoConstraints = false

        return textLabel
    }
}

