//
// Created by 戴显灏 on 11/12/24.
//

#include "PVZYardWidget.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QLabel>
#include <QMouseEvent>

#include "src/src/basic/util/PVZWidgetUtil.h"

PVZYardWidget::PVZYardWidget(QWidget* parent) : QWidget(parent) {
    readyToPlant = false;
    readyToPlantName = QString();
    setupUI();
}

void PVZYardWidget::setReadyToPlant(const QString &seedName, const QPoint &pos) {
    readyToPlant = true;
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    if (readyToPlantName != seedName) {
        readyToPlantName = seedName;
        readyToPlantLabel->setPixmap(PVZResourceLoaderUtil::adjustAlpha(PVZResourceLoaderUtil::loadPlantPixmap(seedName), 0.5));
        readyToPlantLabel->adjustSize();
    }
    setMouseTracking(true);
    readyToPlantLabel->move(pos.x() - readyToPlantLabel->width() / 2, pos.y() - readyToPlantLabel->height() / 2);
    readyToPlantLabel->raise();
    readyToPlantLabel->show();
}

void PVZYardWidget::cancelReadyToPlant() {
    readyToPlant = false;
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    readyToPlantName = QString();
    readyToPlantLabel->hide();
}

void PVZYardWidget::setupUI() {
    setFixedSize(PVZWidgetUtil::mainWidgetWidth, PVZWidgetUtil::mainWidgetHeight);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
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

void PVZYardWidget::mousePressEvent(QMouseEvent *event) {
    if (!readyToPlant) {
        return;
    }
    if (event->button() == Qt::LeftButton) {
    } else if (event->button() == Qt::RightButton) {
        cancelReadyToPlant();
    }
}

