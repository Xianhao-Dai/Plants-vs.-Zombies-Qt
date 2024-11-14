//
// Created by 戴显灏 on 11/12/24.
//

#include "PVZYardWidget.h"

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QLabel>
#include <QMouseEvent>
#include <QtWidgets/qgridlayout.h>

#include "PVZGridWidget.h"
#include "src/src/basic/util/PVZWidgetUtil.h"

static int leftMargin = 30;
static int topMargin = 80;
static int rightMargin = 40;
static int bottomMargin = 40;
static int spacing = 1;
static int gridWidth = (PVZWidgetUtil::mainWidgetWidth - leftMargin - rightMargin) / 9 - spacing;
static int gridHeight = (PVZWidgetUtil::mainWidgetHeight - topMargin - bottomMargin) / 5 - spacing;

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
    grids.resize(5);
    for (int row = 0;row < 5;row++) {
        grids[row].resize(9);
        for (int col = 0;col < 9;col++) {
            grids[row][col] = new PVZGridWidget(row, col, this);
            // grids[row][col]->setFixedSize(gridWidth, gridHeight);
            // grids[row][col]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            grids[row][col]->setAttribute(Qt::WA_TransparentForMouseEvents, true);
            connect(this, &PVZYardWidget::plantGrown, grids[row][col], &PVZGridWidget::plantGrown);
        }
    }
}

void PVZYardWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!readyToPlant) {
        return;
    }
    readyToPlantLabel->move(event->x() - readyToPlantLabel->width() / 2, event->y() - readyToPlantLabel->height() / 2);
}

void PVZYardWidget::mousePressEvent(QMouseEvent *event) {
    if (!readyToPlant) {
        event->ignore();
    }
    if (event->button() == Qt::LeftButton) {
        pair<int, int>index = convertPosToIndex(event->pos());
        if (index.first == -1 || index.second == -1) {
            event->ignore();
        } else {
            plantGrown(readyToPlantName, index);
            cancelReadyToPlant();
        }
    } else if (event->button() == Qt::RightButton) {
        cancelReadyToPlant();
    }
}

pair<int, int> PVZYardWidget::convertPosToIndex(const QPoint& pos) {
    for (int row = 0;row < 5;row++) {
        for (int col = 0;col < 9;col++) {
            if (grids[row][col]->rect().contains(pos)) {
                return make_pair(row, col);
            }
        }
    }
    return make_pair(-1, -1);
}

