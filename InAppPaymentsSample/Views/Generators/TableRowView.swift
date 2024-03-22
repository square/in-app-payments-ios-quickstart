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

class TableRowView : UIStackView {
    var heading: String?
    var title: String?
    var subtitle: String?

    init(heading: String?, title: String?, subtitle: String?) {
        self.heading = heading
        self.title = title
        self.subtitle = subtitle

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
        axis = .horizontal
        distribution = .fillProportionally
        alignment = .top
        spacing = 30
        layoutMargins = UIEdgeInsets(top: 20, left: 0, bottom: 10, right: 0)
        isLayoutMarginsRelativeArrangement = true

        if let heading = heading {
            addArrangedSubview(makeHeadingLabel(text: heading))
        }

        let bodyStackView = UIStackView()
        bodyStackView.axis = .vertical
        bodyStackView.spacing = 6
        addArrangedSubview(bodyStackView)

        if let title = title {
            bodyStackView.addArrangedSubview(makeTitleLabel(text: title))
        }

        if let subtitle = subtitle {
            bodyStackView.addArrangedSubview(makeSubtitleLabel(text: subtitle))
        }
    }
}

extension TableRowView {
    private class HeadlingLabel: UILabel {
        override init(frame: CGRect) {
            super.init(frame: frame)
            commonInit()
        }

        required init?(coder aDecoder: NSCoder) {
            super.init(coder: aDecoder)

            commonInit()
        }

        func commonInit() {
            textColor = Color.heading
            font = UIFont.systemFont(ofSize: 16, weight: .regular)
            translatesAutoresizingMaskIntoConstraints = false
            setContentHuggingPriority(.required, for: .horizontal)
        }

        override var intrinsicContentSize: CGSize {
            return CGSize(width: 54, height: super.intrinsicContentSize.height)
        }
    }

    private func makeHeadingLabel(text: String?) -> UILabel {
        let label = HeadlingLabel()
        label.text = text

        return label
    }

    private func makeTitleLabel(text: String?) -> UILabel {
        let label = UILabel()
        label.text = text
        label.textColor = UIColor.black
        label.font = UIFont.systemFont(ofSize: 16, weight: .medium)

        label.translatesAutoresizingMaskIntoConstraints = false

        return label
    }

    private func makeSubtitleLabel(text: String) -> UILabel {
        let label = UILabel()
        label.numberOfLines = 2
        label.textColor = UIColor(red: 0.48, green: 0.48, blue: 0.48, alpha: 1)
        label.font = UIFont.systemFont(ofSize: 16, weight: .regular)

        let paragraphStyle = NSMutableParagraphStyle()
        let attributes = [NSAttributedString.Key.paragraphStyle : paragraphStyle]
        label.attributedText = NSMutableAttributedString(string: text, attributes: attributes)

        label.translatesAutoresizingMaskIntoConstraints = false

        return label
    }
}
