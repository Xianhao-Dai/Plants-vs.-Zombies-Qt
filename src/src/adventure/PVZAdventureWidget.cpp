//
// Created by 戴显灏 on 11/10/24.
//

#include "PVZAdventureWidget.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

#include "PVZAdventureController.h"
#include "src/src/basic/util/PVZWidgetUtil.h"
#include "src/src/basic/UI/PVZYardWidget.h"

PVZAdventureWidget::PVZAdventureWidget(PVZAdventureController *controller, AdventureScene scene, QWidget *menuWidget) :
controller(controller),
scene(scene),
menuWidget(menuWidget),
mainWindowWidth(PVZWidgetUtil::mainWidgetWidth),
mainWindowHeight(PVZWidgetUtil::mainWidgetHeight) {
    loadCachedPixmaps();
    setUpUI();
    connect(controller, &PVZAdventureController::seedPickDidFinished, this, &PVZAdventureWidget::moveBack);
}

void PVZAdventureWidget::loadCachedPixmaps() {
    QString bgPath = "";
    switch (scene) {
        case BareYard:
            bgPath = "/game_scene/scene_bare_yard.jpg";
        break;
        case YardDaytime:
            bgPath = "/game_scene/scene_yard_daytime.jpg";
        break;
        case YardNight:
            bgPath = "/game_scene/scene_yard_night.jpg";
        break;
        case PoolDaytime:
            bgPath = "/game_scene/scene_pool_daytime.jpg";
        break;
        case PoolNight:
            bgPath = "/game_scene/scene_pool_night.jpg";
        break;
        case RoofDaytime:
            bgPath = "/game_scene/scene_roof_daytime.jpg";
        break;
        case RoofNight:
            bgPath = "/game_scene/scene_roof_night.jpg";
        break;
        default:
            break;
    }
    bgPixmap = PVZResourceLoaderUtil::loadFullWindowPixmap(bgPath);
}

void PVZAdventureWidget::setUpUI() {
    this->setFixedSize(mainWindowWidth, mainWindowHeight);
    this->setWindowTitle("Plants Vs. Zombies");
    bgLabel = new QLabel(this);
    bgLabel->move(0, 0);
    bgLabel->setFixedSize(bgPixmap.size());
    bgLabel->setPixmap(bgPixmap);

    QPropertyAnimation *bgAnimation = new QPropertyAnimation(bgLabel, "pos");
    bgAnimation->setDuration(2000);
    bgAnimation->setStartValue(QPoint(0, 0));
    bgAnimation->setEndValue(QPoint(mainWindowWidth - bgPixmap.width(), 0));
    bgAnimation->setEasingCurve(QEasingCurve::OutQuart);
    QTimer::singleShot(1500, [=]() {
        bgAnimation->start();
    });
    connect(bgAnimation, &QPropertyAnimation::finished, [=]() {
        this->bgAnimationFinished_1();
    });
}

void PVZAdventureWidget::moveBack() {
    QPropertyAnimation *bgAnimation = new QPropertyAnimation(bgLabel, "pos");
    bgAnimation->setDuration(2000);
    bgAnimation->setStartValue(QPoint(mainWindowWidth - bgPixmap.width(), 0));
    bgAnimation->setEndValue(QPoint(-220, 0));
    bgAnimation->setEasingCurve(QEasingCurve::OutQuart);
    bgAnimation->start();
    connect(bgAnimation, &QPropertyAnimation::finished, [=]() {
        this->bgAnimationFinished_2();
    });
}
