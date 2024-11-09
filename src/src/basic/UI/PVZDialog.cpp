//
// Created by 戴显灏 on 11/8/24.
//

#include "PVZDialog.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QPainter>
#include <QVBoxLayout>

#include "PVZDialogButton.h"
#include "PVZPushButton.h"

PVZDialog::PVZDialog(QString title, QString message) : QDialog() {
    dialogWidth = 600;
    dialogHeight = 500;
    this->setFixedSize(dialogWidth, dialogHeight);
    buttonsWidget = new QWidget(this);
    QVBoxLayout *dialogLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonsWidget);
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setSpacing(30);
    QSpacerItem *spacer = new QSpacerItem(0, dialogHeight - 112, QSizePolicy::Expanding, QSizePolicy::Fixed);
    dialogLayout->addSpacerItem(spacer);
    dialogLayout->addWidget(buttonsWidget);
    buttonsWidget->setLayout(buttonLayout);
    this->setLayout(dialogLayout);
    this->setStyleSheet("background-color:transparent");
}

void PVZDialog::addButton(QString text, std::function<void()>clicked) {
    PVZDialogButton *btn = new PVZDialogButton(this , text);
    buttonsWidget->layout()->addWidget(btn);
    connect(btn, &PVZPushButton::clicked, clicked);
}

void PVZDialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap header = PVZResourceLoaderUtil::loadPixmap("/bg/dialog_header.png");
    QPixmap topLeft = PVZResourceLoaderUtil::loadPixmap("/bg/dialog_top_left.png");
    QPixmap topRight = PVZResourceLoaderUtil::loadPixmap("/bg/dialog_top_right.png");
    QPixmap bottomLeft = PVZResourceLoaderUtil::loadPixmap("/bg/dialog_bottom_left.png");
    QPixmap bottomRight = PVZResourceLoaderUtil::loadPixmap("/bg/dialog_bottom_right.png");

    int headerHeight = header.height() - 5; // compensate for resources' missing pixels
    int headerWidth = header.width();
    int topHeight = topLeft.height();
    int bottomHeight = bottomLeft.height();
    int leftWidth = topLeft.width();
    int rightWidth = topRight.width();

    QPixmap topMiddle = PVZResourceLoaderUtil::loadScaledPixmapOnWidth("/bg/dialog_top_middle.png", dialogWidth - leftWidth - rightWidth);
    QPixmap bottomMiddle = PVZResourceLoaderUtil::loadScaledPixmapOnWidth("/bg/dialog_bottom_middle.png", dialogWidth - leftWidth - rightWidth);
    QPixmap leftMiddle = PVZResourceLoaderUtil::loadScaledPixmapOnHeight("/bg/dialog_left_middle.png", dialogHeight - headerHeight - topHeight - bottomHeight);
    QPixmap rightMiddle = PVZResourceLoaderUtil::loadScaledPixmapOnHeight("/bg/dialog_right_middle.png", dialogHeight - headerHeight - topHeight - bottomHeight);
    QPixmap center = PVZResourceLoaderUtil::loadScaledPixmap("/bg/dialog_center.png", dialogWidth - leftWidth - rightWidth, dialogHeight - headerHeight - topHeight - bottomHeight);
    QPixmap bg = PVZResourceLoaderUtil::verticallyJoinPixmaps({
        PVZResourceLoaderUtil::horizontallyJoinPixmaps({
            topLeft, topMiddle, topRight,
        }, Qt::AlignTop),
        PVZResourceLoaderUtil::horizontallyJoinPixmaps({
            leftMiddle, center, rightMiddle,
        }, Qt::AlignTop),
        PVZResourceLoaderUtil::horizontallyJoinPixmaps({
            bottomLeft, bottomMiddle, bottomRight,
        }, Qt::AlignTop)
    }, Qt::AlignLeft);

    painter.drawPixmap(dialogWidth / 2 - headerWidth / 2, 0, header);
    painter.drawPixmap(0, headerHeight, bg);
}
