//
// Created by 戴显灏 on 11/6/24.
//

#ifndef GAMESTARTWIDGET_H
#define GAMESTARTWIDGET_H
#include <QPushButton>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QLabel>


class PVZPushButton;

class PVZGameStartWidget : public QWidget {
    Q_OBJECT
public:
    explicit PVZGameStartWidget(QWidget *parent = nullptr);
private:
    // cached pixmap
    QPixmap bgPixmap;
    QPixmap grassPixmap;
    QPixmap grassRollPixmap;

    // UI
    PVZPushButton *startButton;
    QLabel *grassLabel;
    QLabel *grassRollLabel;

    const int mainWindowWidth;
    const int mainWindowHeight;

    int angle;

    void loadCachedPixmaps();
    void setUpUI();
    void playAnimation();

    void paintEvent(QPaintEvent *event) override;

};

#endif //GAMESTARTWIDGET_H
