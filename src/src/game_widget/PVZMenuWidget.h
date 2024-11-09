//
// Created by 戴显灏 on 11/8/24.
//

#ifndef PVZMENUWIDGET_H
#define PVZMENUWIDGET_H

#include <QWidget>


class PVZDialog;
class PVZPushButton;

class PVZMenuWidget : public QWidget {
    Q_OBJECT
public:
    explicit PVZMenuWidget(QWidget *parent = nullptr);
private:
    PVZPushButton *startAdventureButton;
    PVZPushButton *survivalButton;
    PVZPushButton *puzzleButton;
    PVZPushButton *miniGamesButton;
    PVZPushButton *changeNameButton;
    PVZDialog *changeNameDialog;

    const int mainWindowWidth;
    const int mainWindowHeight;

    void loadCachedPixmaps();
    void setUpUI();

    void paintEvent(QPaintEvent *event) override;
};



#endif //PVZMENUWIDGET_H
