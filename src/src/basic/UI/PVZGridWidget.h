//
// Created by 戴显灏 on 11/12/24.
//

#ifndef PVZGRIDWIDGET_H
#define PVZGRIDWIDGET_H
#include <QtWidgets/qgridlayout.h>

#include "src/src/adventure/PVZAdventureWidget.h"

using namespace std;

class PVZGridWidget : public QWidget {
    Q_OBJECT
public:
    explicit PVZGridWidget(int row, int col, QWidget* parent = nullptr);
    void plantGrown(const QString &seedName, pair<int, int>index);
    bool canPlant(const QString &seedName);
private:
    int row;
    int col;
    QLabel *plantLabel;
    void setupUI();
};



#endif //PVZGRIDWIDGET_H
