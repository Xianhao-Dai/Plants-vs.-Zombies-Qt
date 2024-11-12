//
// Created by 戴显灏 on 11/10/24.
//

#ifndef PVZADVENTURECONTROLLER_H
#define PVZADVENTURECONTROLLER_H
#include <QMouseEvent>
#include <QtCore/qobject.h>


class PVZAdventureWidget;
class PVZYardWidget;
class PVZSeedBankWidget;
class QLabel;

class PVZAdventureController : public QObject {
    Q_OBJECT
public:
    void runAdventure();
private:
    std::pair<int, int> adventureLevel;
    PVZAdventureWidget* adventureWidget;
    PVZSeedBankWidget *bank;
    PVZYardWidget *yard;

    void setUpUI();
    void setUpDefaultGame();
    void setUpSelfPickGame();
signals:
    void seedPickDidFinished();
};



#endif //PVZADVENTURECONTROLLER_H
