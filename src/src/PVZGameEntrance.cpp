//
// Created by 戴显灏 on 11/6/24.
//

#include "PVZGameEntrance.h"

#include <QApplication>

#include "basic/util/PVZWidgetUtil.h"
#include "game_widget/PVZGameStartWidget.h"

int PVZGameEntrance::run(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PVZGameStartWidget *widget = new PVZGameStartWidget(nullptr);

    widget->setFixedSize(PVZWidgetUtil::mainWidgetWidth, PVZWidgetUtil::mainWidgetHeight);
    widget->setWindowTitle("Plants Vs. Zombies");
    widget->show();

    return QApplication::exec();
}

