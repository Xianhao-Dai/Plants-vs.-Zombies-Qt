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
    QVBoxLayout *layout = new QVBoxLayout(this);
    // QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    // layout->addSpacerItem(spacer);
    plantLabel = new QLabel();
    // plantLabel->setScaledContents(true);
    plantLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    layout->addWidget(plantLabel);
}

void PVZGridWidget::plantGrown(const QString &seedName, pair<int, int>index) {
    if (index.first != row || index.second != col) {
        return;
    }
    QMovie *movie = new QMovie(":/default/src/assets/plants/" + seedName + ".gif");
    movie->start();
    PVZResourceLoaderUtil::resizeMovie(movie, this->width(), 0, Qt::KeepAspectRatio);
    plantLabel->setMovie(movie);
}
