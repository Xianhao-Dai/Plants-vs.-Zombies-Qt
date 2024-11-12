//
// Created by 戴显灏 on 11/11/24.
//

#include "PVZSeedBankWidget.h"

#include <qboxlayout.h>

#include "src/src/basic/util/PVZResourceLoaderUtil.h"

#include <QPainter>

#include "PVZSeedCardButton.h"
#include "src/src/basic/util/PVZWidgetUtil.h"

static int leftMargin = 12;
static int topMargin = 8;
static int rightMargin = 10;
static int bottomMargin = 8;
static int labelWidith = 60;
static int labelHeight = 20;
static int buttonSpacing = 2;
static int seedBankWidgetWidth = PVZWidgetUtil::seedBankWidgetWidth;
static int seedBankWidgetHeight = PVZWidgetUtil::seedBankWidgetHeight;

PVZSeedBankWidget::PVZSeedBankWidget(vector<QString> seeds, QWidget* parent) : seeds(seeds), QWidget(parent) {
    setUpUI();
}

void PVZSeedBankWidget::setUpUI() {
    setFixedSize(seedBankWidgetWidth, seedBankWidgetHeight);
    int seedCardWidth = (seedBankWidgetWidth - leftMargin - labelWidith - rightMargin) / 6 - buttonSpacing;
    int seedCardHeight = seedBankWidgetHeight - topMargin - bottomMargin;
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(buttonSpacing);
    layout->setContentsMargins(leftMargin, topMargin, rightMargin, bottomMargin);
    QVBoxLayout *labelLayout = new QVBoxLayout();
    QSpacerItem *verticalSpacer = new QSpacerItem(labelWidith, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    labelLayout->addItem(verticalSpacer);
    labelLayout->setSpacing(0);
    labelLayout->setContentsMargins(0, 0, 0, 0);
    sunNumLabel = new QLabel(this);
    sunNumLabel->setAlignment(Qt::AlignCenter);
    sunNumLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sunNumLabel->setFixedSize(labelWidith, labelHeight);
    sunNumLabel->setText("0");
    sunNumLabel->setFont(QFont("Arial", 20, QFont::Bold));
    labelLayout->addWidget(sunNumLabel);
    layout->addLayout(labelLayout);
    QSpacerItem *spacerBetweenLabelAndButton = new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    layout->addSpacerItem(spacerBetweenLabelAndButton);
    QSpacerItem *rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    for (int i = 0; i < seeds.size() && i < 6; i++) {
        PVZSeedCardButton *button = new PVZSeedCardButton(seeds[i], QSize(seedCardWidth, seedCardHeight));
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, [=]() {
            seedDidClicked(seeds[i]);
        });
    }
    layout->addSpacerItem(rightSpacer);
}

void PVZSeedBankWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap bg = PVZResourceLoaderUtil::loadScaledPixmap("/bg/bg_seed_bank.png", PVZWidgetUtil::seedBankWidgetWidth, PVZWidgetUtil::seedBankWidgetHeight);
    painter.drawPixmap(0, 0, bg);
}
