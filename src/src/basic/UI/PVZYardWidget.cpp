//
// Created by 戴显灏 on 11/12/24.
//

#include "PVZYardWidget.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QLabel>
#include <QMouseEvent>

PVZYardWidget::PVZYardWidget(QWidget* parent) : QWidget(parent) {
    readyToPlant = false;
    readyToPlantName = QString();
    setupUI();
}

void PVZYardWidget::setReadyToPlant(const QString &seedName) {
    readyToPlant = true;
    if (readyToPlantName != seedName) {
        readyToPlantName = seedName;
        readyToPlantLabel->setPixmap(PVZResourceLoaderUtil::adjustAlpha(PVZResourceLoaderUtil::loadPlantPixmap(seedName), 0.5));
        readyToPlantLabel->adjustSize();
    }
    setMouseTracking(true);
    readyToPlantLabel->show();
}

void PVZYardWidget::cancelReadyToPlant() {
    readyToPlant = false;
    readyToPlantName = QString();
    readyToPlantLabel->hide();
}

void PVZYardWidget::setupUI() {
    setFixedSize(750, 500);
    setStyleSheet("border : 1px solid red");
    readyToPlantLabel = new QLabel(this);
    readyToPlantLabel->hide();
    readyToPlantLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void PVZYardWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!readyToPlant) {
        return;
    }
    readyToPlantLabel->move(event->x() - readyToPlantLabel->width() / 2, event->y() - readyToPlantLabel->height() / 2);
}
