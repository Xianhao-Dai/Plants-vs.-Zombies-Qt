//
// Created by 戴显灏 on 11/12/24.
//

#include "PVZGridWidget.h"

#include <QMovie>
#include <QLabel>
#include <QPalette>

#include "src/src/basic/util/PVZResourceLoaderUtil.h"


PVZGridWidget::PVZGridWidget(int row, int col, QWidget* parent) : QWidget(parent), row(row), col(col) {
    setupUI();
}

void PVZGridWidget::setupUI() {
    plantLabel = new QLabel(this);
    plantLabel->setScaledContents(true);
    plantLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void PVZGridWidget::growPlant(const QString &seedName) {
    if (!this->canPlant(seedName)) {
        return;
    }
    QMovie *movie = new QMovie(":/default/src/assets/plants/" + seedName + ".gif");
    movie->start();
    QSize size = PVZResourceLoaderUtil::resizeMovie(movie, this->width(), 0, Qt::KeepAspectRatio);
    plantLabel->resize(size);
    plantLabel->move(0, this->height() - size.height());
    plantLabel->setMovie(movie);
}

bool PVZGridWidget::canPlant(const QString &seedName) {
    return true;
}
