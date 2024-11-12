//
// Created by 戴显灏 on 11/10/24.
//

#ifndef PVZADVENTUREWIDGET_H
#define PVZADVENTUREWIDGET_H
#include <QtWidgets/qwidget.h>

class PVZYardWidget;
class PVZAdventureController;

enum AdventureScene {
    BareYard = 0x000,
    YardDaytime = 0x001,
    YardNight = 0x002,
    PoolDaytime = 0x003,
    PoolNight = 0x004,
    RoofDaytime = 0x005,
    RoofNight = 0x006,
};
class QLabel;

class PVZAdventureWidget : public QWidget {
    Q_OBJECT
public:
    explicit PVZAdventureWidget(PVZAdventureController *controller, AdventureScene scene, QWidget *menuWidget = nullptr);

private:
    QPixmap bgPixmap;

    PVZAdventureController *controller;
    QWidget *menuWidget;
    QLabel *bgLabel;
    AdventureScene scene;

    const int mainWindowWidth;
    const int mainWindowHeight;

    void loadCachedPixmaps();
    void setUpUI();
    void moveBack();

signals:
    void bgAnimationFinished_1();
    void bgAnimationFinished_2();
};



#endif //PVZADVENTUREWIDGET_H
