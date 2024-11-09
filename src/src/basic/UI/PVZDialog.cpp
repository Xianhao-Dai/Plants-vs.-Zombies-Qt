//
// Created by 戴显灏 on 11/8/24.
//

#include "PVZDialog.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QPainter>
#include <QVBoxLayout>

#include "PVZDialogButton.h"
#include "PVZPushButton.h"

PVZDialog::PVZDialog(QString title, QString message) : QDialog(), buttons(), title(title), message(message) {
    setUpUI();
}

void PVZDialog::addButton(QString text, std::function<void()>clicked) {
    PVZDialogButton *btn = new PVZDialogButton(this , text);
    buttons.push_back(btn);
    buttonsLayout->addWidget(btn);
    connect(btn, &PVZPushButton::clicked, clicked);
}

void PVZDialog::addAdditionalWidget(QWidget *widget) {
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    verticalLayout->insertWidget(3, widget);
    verticalLayout->setAlignment(widget, Qt::AlignCenter);
}

void PVZDialog::setUpUI() {
    dialogWidth = 600;
    dialogHeight = 500;

    titleLabel = new QLabel(title, this);
    titleLabel->setFont(QFont("Chalkduster", 40, QFont::Bold));
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleLabel->setStyleSheet("color: rgb(0, 255, 0);");
    messageLabel = new QLabel(message, this);
    messageLabel->setFont(QFont("Chalkduster", 20, QFont::Bold));
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setWordWrap(true);
    messageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    messageLabel->setStyleSheet("color: rgb(255, 255, 255);");

    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    QSpacerItem *leftSpacer = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    horizontalLayout->addSpacerItem(leftSpacer);
    verticalLayout = new QVBoxLayout();
    QSpacerItem *topSpacer = new QSpacerItem(0, 70, QSizePolicy::Expanding, QSizePolicy::Fixed);
    verticalLayout->addSpacerItem(topSpacer);
    verticalLayout->addWidget(titleLabel);
    verticalLayout->addWidget(messageLabel);
    QWidget *buttonsWidget = new QWidget(this);
    buttonsWidget->setFixedHeight(80);
    buttonsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(30);
    buttonsWidget->setLayout(buttonsLayout);
    verticalLayout->addWidget(buttonsWidget);
    horizontalLayout->addLayout(verticalLayout);
    QSpacerItem *rightSpacer = new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    horizontalLayout->addSpacerItem(rightSpacer);

    this->setFixedSize(dialogWidth, dialogHeight);
    this->setStyleSheet("background-color:transparent");
}

void PVZDialog::setLayout(QLayout *layout) {
    this->QWidget::setLayout(layout);
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
