//
// Created by 戴显灏 on 11/10/24.
//

#include "PVZSeedPickerWidget.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QPainter>

#include "PVZSeedCardButton.h"
#include "src/src/basic/util/PVZResourceLoaderUtil.h"
#include "src/src/basic/util/PVZWidgetUtil.h"


PVZSeedPickerWidget::PVZSeedPickerWidget(vector<QString> enabledSeeds, vector<QString> disabledSeeds, QWidget* parent) : enabledSeeds(enabledSeeds), disabledSeeds(disabledSeeds), QWidget(parent) {
    setUpUI();
}

void PVZSeedPickerWidget::setUpUI() {
    setFixedSize(PVZWidgetUtil::seedPickerWidgetWidth, PVZWidgetUtil::seedPickerWidgetHeight);

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setStyleSheet("background: transparent;");
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background: transparent; border: none;");
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setSpacing(1);
    gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    for (int i = 0; i < enabledSeeds.size(); i++) {
        int row = i / 6;
        int col = i % 6;
        QString seedName = enabledSeeds.at(i);
        PVZSeedCardButton *seedCard = new PVZSeedCardButton(seedName, QSize(75, 112));
        connect(seedCard, &QPushButton::clicked, [=]() {
            this->seedDidPicked(seedName, row, col);
        });
        gridLayout->addWidget(seedCard, row, col);
    }
    for (int i = enabledSeeds.size(); i < disabledSeeds.size() + enabledSeeds.size(); i++) {
        int row = i / 6;
        int col = i % 6;
        QString seedName = disabledSeeds.at(i - enabledSeeds.size());
        PVZSeedCardButton *seedCard = new PVZSeedCardButton(seedName, QSize(75, 112), false);
        gridLayout->addWidget(seedCard, row, col);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 30, 0, -20);
    mainLayout->addWidget(scrollArea);
}

void PVZSeedPickerWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap bg = PVZResourceLoaderUtil::loadScaledPixmap("/bg/bg_seed_picker.png", PVZWidgetUtil::seedPickerWidgetWidth, PVZWidgetUtil::seedPickerWidgetHeight);
    painter.drawPixmap(0, 0, bg);
}
