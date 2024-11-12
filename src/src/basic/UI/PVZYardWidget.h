//
// Created by 戴显灏 on 11/12/24.
//

#ifndef PVZYARDWIDGET_H
#define PVZYARDWIDGET_H
#include <QPropertyAnimation>

#include "src/src/adventure/PVZAdventureWidget.h"


class PVZYardWidget : public QWidget {
public:
    explicit PVZYardWidget(QWidget* parent = nullptr);
    void setReadyToPlant(const QString &seedName);
private:
    void setupUI();
    void mouseMoveEvent(QMouseEvent *event) override;
    bool readyToPlant; // true if select a certain plant in seed bank
    QString readyToPlantName; // selected plant name
    QLabel *readyToPlantLabel;

    void cancelReadyToPlant();
};



#endif //PVZYARDWIDGET_H
