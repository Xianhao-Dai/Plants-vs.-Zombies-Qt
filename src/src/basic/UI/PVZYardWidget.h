//
// Created by 戴显灏 on 11/12/24.
//

#ifndef PVZYARDWIDGET_H
#define PVZYARDWIDGET_H
#include <QPropertyAnimation>

#include "src/src/adventure/PVZAdventureWidget.h"

class PVZGridWidget;
class QGridLayout;
using namespace std;

class PVZYardWidget : public QWidget {
    Q_OBJECT
public:
    explicit PVZYardWidget(QWidget* parent = nullptr);
    void setReadyToPlant(const QString &seedName, const QPoint &pos);
private:
    void setupUI();
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    bool readyToPlant; // true if select a certain plant in seed bank
    QString readyToPlantName; // selected plant name
    QLabel *readyToPlantLabel;

    vector<vector<PVZGridWidget *>> grids;

    void cancelReadyToPlant();
    static pair<int, int> convertPosToIndex(const QPoint& pos);
};



#endif //PVZYARDWIDGET_H
