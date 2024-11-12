//
// Created by 戴显灏 on 11/10/24.
//

#ifndef PVZSEEDPICKERWIDGET_H
#define PVZSEEDPICKERWIDGET_H
#include "src/src/adventure/PVZAdventureWidget.h"

class QGridLayout;
using namespace std;

class PVZSeedPickerWidget : public QWidget {
    Q_OBJECT
public:
    explicit PVZSeedPickerWidget(vector<QString> enabledSeeds, vector<QString> disabledSeeds={}, QWidget* parent = nullptr);
    void removeSelectedSeeds(QString seedName, int row, int col);
private:
    QGridLayout *gridLayout;
    vector<QString> enabledSeeds;
    vector<QString> disabledSeeds;
    void setUpUI();
    void paintEvent(QPaintEvent *event) override;
signals:
    void seedDidPicked(QString seedName, int row, int col);
};



#endif //PVZSEEDPICKERWIDGET_H
