//
// Created by 戴显灏 on 11/8/24.
//

#ifndef PVZMENUWIDGET_H
#define PVZMENUWIDGET_H

#include <QWidget>
#include <QtWidgets/QLabel>


class QLineEdit;
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
    QLabel *nameLabel;
    PVZDialog *changeNameDialog;
    QLineEdit* nameLineEdit;

    const int mainWindowWidth;
    const int mainWindowHeight;

    void loadCachedPixmaps();
    void setUpUI();

    void paintEvent(QPaintEvent *event) override;
};



#endif //PVZMENUWIDGET_H
