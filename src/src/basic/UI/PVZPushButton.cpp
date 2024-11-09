//
// Created by 戴显灏 on 11/7/24.
//

#include "PVZPushButton.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QPropertyAnimation>

PVZPushButton::PVZPushButton(QWidget *parent, QString iconPath, QString highlightIconPath) :QPushButton(parent) {
    this->iconPath = iconPath;
    this->highlightedIconPath = highlightIconPath;

    icon = PVZResourceLoaderUtil::loadPixmap(iconPath);
    if (!highlightIconPath.isEmpty()) {
        highlightedIcon = PVZResourceLoaderUtil::loadPixmap(highlightIconPath);
    } else {
        highlightedIcon = PVZResourceLoaderUtil::adjustBrightness(icon, 0.6);
    }
    this->setStyleSheet("QPushButton{"
                        "border:0px;"
                        "}");
    this->setIcon(icon);
    this->setIconSize(QSize(icon.width(), icon.height()));
    this->setFixedSize(QSize(icon.width(), icon.height()));
    connect(this, &PVZPushButton::pressed, [=]() {
        this->setIcon(highlightedIcon);
    });
    connect(this, &PVZPushButton::released, [=]() {
        this->setIcon(icon);
    });

    textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setFixedSize(this->size());
}

void PVZPushButton::setText(const QString &text) {
    textLabel->setText(text);
}

void PVZPushButton::setFont(const QFont &font) {
    textLabel->setFont(font);
}