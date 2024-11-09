//
// Created by 戴显灏 on 11/6/24.
//

#include "PVZGameStartWidget.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"
#include "src/src/basic/util/PVZWidgetUtil.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTimer>

#include "PVZMenuWidget.h"
#include "src/src/basic/UI/PVZPushButton.h"

PVZGameStartWidget::PVZGameStartWidget(QWidget *parent) :
QWidget(parent),
mainWindowWidth(PVZWidgetUtil::mainWidgetWidth),
mainWindowHeight(PVZWidgetUtil::mainWidgetHeight) {
    angle = 0;
    loadCachedPixmaps();
    setUpUI();
    playAnimation();
}

void PVZGameStartWidget::loadCachedPixmaps() {
    grassPixmap = PVZResourceLoaderUtil::loadScaledPixmap("/bg/loading_grass.png", mainWindowWidth / 3, 0);
    grassRollPixmap = PVZResourceLoaderUtil::loadPixmap("/bg/loading_grass_roll.png");
    bgPixmap = PVZResourceLoaderUtil::loadFullWindowPixmap("/bg/loading_game_start.jpg");
}

void PVZGameStartWidget::setUpUI() {
    startButton = new PVZPushButton(this, "/bg/loading_dirt.png");
    startButton->move(mainWindowWidth / 3, mainWindowHeight * 3 / 4);
    connect(startButton, &PVZPushButton::clicked, [=]() {
        QTimer::singleShot(100, [=]() {
            this->destroy();
            PVZMenuWidget *menuWidget = new PVZMenuWidget();
            menuWidget->show();
        });
    });

    int horizontalOffset = 5;
    int verticalOffset_1 = 20;
    int verticalOffset_2 = 40;

    grassLabel = new QLabel();
    grassLabel->setParent(this);
    grassLabel->setAlignment(Qt::AlignLeft);
    grassLabel->resize(grassPixmap.width(), grassPixmap.height());
    grassLabel->move(mainWindowWidth / 3 - horizontalOffset, mainWindowHeight * 3 / 4 - verticalOffset_1);
    grassLabel->setPixmap(grassPixmap);

    grassRollLabel = new QLabel();
    grassRollLabel->setParent(this);
    grassRollLabel->setScaledContents(true);
    grassRollLabel->resize(grassRollPixmap.width(), grassRollPixmap.width());
    grassRollLabel->move(mainWindowWidth / 3 - horizontalOffset, mainWindowHeight * 3 / 4 - verticalOffset_1 - verticalOffset_2);
    grassRollLabel->setPixmap(grassRollPixmap);
}

void PVZGameStartWidget::playAnimation() {
    QPropertyAnimation *grassAnimation = new QPropertyAnimation(grassLabel, "geometry");
    grassAnimation->setDuration(4000);
    grassAnimation->setStartValue(QRect(grassLabel->x(), grassLabel->y(), 0, grassLabel->height()));
    grassAnimation->setEndValue(QRect(grassLabel->x(), grassLabel->y(), grassLabel->width(), grassLabel->height()));
    grassAnimation->setEasingCurve(QEasingCurve::Linear);
    grassAnimation->start();

    // QPropertyAnimation *geometry = new QPropertyAnimation(grassRollLabel, "geometry");
    // geometry->setDuration(4000);
    // geometry->setStartValue(QRect(grassRollLabel->x(), grassRollLabel->y(), grassRollLabel->width(), grassRollLabel->height()));
    // geometry->setEndValue(QRect(grassRollLabel->x() + mainWindowWidth / 3 + grassRollLabel->width() - 40, grassRollLabel->y() + grassRollLabel->height() - 40, 40, 40));
    // geometry->setEasingCurve(QEasingCurve::Linear);
    // geometry->start();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        angle += 7;
        grassRollLabel->setPixmap(PVZResourceLoaderUtil::rotatedPixmap(grassRollPixmap, angle));
    });
    timer->start(20);

}

void PVZGameStartWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, bgPixmap);
}
