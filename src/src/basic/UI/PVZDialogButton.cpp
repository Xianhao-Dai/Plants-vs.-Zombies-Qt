//
// Created by 戴显灏 on 11/9/24.
//

#include "PVZDialogButton.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QLabel>
#include <QPainter>

PVZDialogButton::PVZDialogButton(QWidget *parent, QString text) : QPushButton(parent) {
    QFont font("Chalkduster", 20, QFont::Bold);
    QFontMetrics m(font);
    QRect rec = m.boundingRect(text);
    buttonWidth = rec.width() + 100; // button horizontal margin
    buttonHeight = 50; // button vertical margin added
    QPixmap left = PVZResourceLoaderUtil::loadScaledPixmapOnHeight("/bg/dialog_button_left.png", buttonHeight);
    QPixmap right = PVZResourceLoaderUtil::loadScaledPixmapOnHeight("/bg/dialog_button_right.png", buttonHeight);
    QPixmap middle = PVZResourceLoaderUtil::loadScaledPixmap("/bg/dialog_button_middle.png", buttonWidth - left.width() - right.width(), buttonHeight);
    icon = PVZResourceLoaderUtil::horizontallyJoinPixmaps({left, middle, right});
    highlightedIcon = PVZResourceLoaderUtil::adjustBrightness(icon, 0.6);
    this->setIcon(icon);
    this->setIconSize(QSize(buttonWidth, buttonHeight));
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFixedSize(buttonWidth, buttonHeight);
    connect(this, &PVZDialogButton::pressed, [=]() {
        this->setIcon(highlightedIcon);
    });
    connect(this, &PVZDialogButton::released, [=]() {
        this->setIcon(icon);
    });
    textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setFixedSize(this->size());
    textLabel->move(0, 0);
    textLabel->setFont(font);
    textLabel->setText(text);
}