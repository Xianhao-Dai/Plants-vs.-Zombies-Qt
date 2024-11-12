//
// Created by 戴显灏 on 11/11/24.
//

#ifndef PVZSEEDBANKWIDGET_H
#define PVZSEEDBANKWIDGET_H
#include "src/src/adventure/PVZAdventureWidget.h"

#include <vector>
using namespace std;


class PVZSeedBankWidget : public QWidget {
    Q_OBJECT
public:
    explicit PVZSeedBankWidget(vector<QString> seeds, QWidget* parent = nullptr);
private:
    vector<QString> seeds;
    QLabel* sunNumLabel;
    void setUpUI();
    void paintEvent(QPaintEvent *event) override;
signals:
    void seedDidClicked(QString seed);

};



#endif //PVZSEEDBANKWIDGET_H
