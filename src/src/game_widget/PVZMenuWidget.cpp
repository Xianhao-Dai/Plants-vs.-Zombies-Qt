//
// Created by 戴显灏 on 11/8/24.
//

#include "PVZMenuWidget.h"

#include <QApplication>

#include "src/src/basic/util/PVZResourceLoaderUtil.h"
#include "src/src/basic/util/PVZWidgetUtil.h"
#include "src/src/basic/UI/PVZPushButton.h"
#include "src/src/basic/UI/PVZDialog.h"

#include <QPainter>
#include <QLineEdit>

PVZMenuWidget::PVZMenuWidget(QWidget *parent) :
QWidget(parent),
mainWindowWidth(PVZWidgetUtil::mainWidgetWidth),
mainWindowHeight(PVZWidgetUtil::mainWidgetHeight)  {
    setUpUI();
}

void PVZMenuWidget::setUpUI() {
    this->setFixedSize(mainWindowWidth, mainWindowHeight);
    this->setWindowTitle("Plants Vs. Zombies");

    startAdventureButton = new PVZPushButton(this, "/bg/menu_start_adventure");
    startAdventureButton->move(585, 20);
    miniGamesButton = new PVZPushButton(this, "/bg/menu_mini_games");
    miniGamesButton->move(590, 135);
    puzzleButton = new PVZPushButton(this, "/bg/menu_puzzle");
    puzzleButton->move(595, 220);
    survivalButton = new PVZPushButton(this, "/bg/menu_survival");
    survivalButton->move(600, 300);
    changeNameButton = new PVZPushButton(this, "/bg/menu_change_name");
    changeNameButton->move(50, 135);
    changeNameDialog = new PVZDialog("Change Your Name", "You may change your name if it's not your account!");
    changeNameDialog->setModal(true);
    changeNameDialog->setWindowFlag(Qt::FramelessWindowHint);
    changeNameDialog->addButton("Confirm", [=]() {
        changeNameDialog->hide();
        nameLineEdit->setText("");
        nameLineEdit->clearFocus();
    });
    changeNameDialog->addButton("Cancel", [=]() {
        changeNameDialog->hide();
        nameLineEdit->setText("");
        nameLineEdit->clearFocus();
    });
    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText("Enter your name");
    nameLineEdit->setAlignment(Qt::AlignCenter);
    nameLineEdit->setFocusPolicy(Qt::ClickFocus);
    nameLineEdit->setFont(QFont("Chalkduster", 20, QFont::Bold));
    nameLineEdit->setMaxLength(20);
    nameLineEdit->setFixedWidth(300);
    nameLineEdit->setStyleSheet("color: rgb(255, 255, 255); background-color: rgb(0, 0, 0);");
    changeNameDialog->addAdditionalWidget(nameLineEdit);
    connect(changeNameButton, &PVZPushButton::clicked, this, [=]() {
        changeNameDialog->show();
    });
}

void PVZMenuWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap sky = PVZResourceLoaderUtil::loadFullWindowPixmap("/bg/menu_sky.jpg");
    QPixmap tree = PVZResourceLoaderUtil::loadScaledPixmap("/bg/menu_tree.png", 0, mainWindowHeight, Qt::KeepAspectRatio);
    QPixmap ground = PVZResourceLoaderUtil::loadScaledPixmap("/bg/menu_ground.png", 0, mainWindowHeight, Qt::KeepAspectRatio);
    QPixmap tomb = PVZResourceLoaderUtil::loadScaledPixmap("/bg/menu_tomb.png", 0, mainWindowHeight, Qt::KeepAspectRatio);
    QPixmap cloud1 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_cloud_1.png");
    QPixmap cloud2 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_cloud_2.png");
    QPixmap cloud3 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_cloud_3.png");
    QPixmap cloud4 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_cloud_4.png");
    QPixmap cloud5 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_cloud_5.png");
    QPixmap cloud6 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_cloud_6.png");
    QPixmap shadow1 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_shadow_start_adventure.png");
    QPixmap shadow2 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_shadow_mini_games.png");
    QPixmap shadow3 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_shadow_puzzle.png");
    QPixmap shadow4 = PVZResourceLoaderUtil::loadPixmap("/bg/menu_shadow_survival.png");
    QPixmap welcome = PVZResourceLoaderUtil::loadPixmap("/bg/menu_welcome_back.png");

    painter.drawPixmap(0, 0, sky);
    painter.drawPixmap(0, 270, ground);
    painter.drawPixmap(200, 100, cloud1);
    painter.drawPixmap(300, 175, cloud2);
    painter.drawPixmap(300, 0, cloud3);
    painter.drawPixmap(500, 150, cloud4);
    painter.drawPixmap(600, 200, cloud5);
    painter.drawPixmap(100, 300, cloud6);
    painter.drawPixmap(0, 0, tree);
    painter.drawPixmap(mainWindowWidth - tomb.width(), 0, tomb);
    painter.drawPixmap(585, 20, shadow1);
    painter.drawPixmap(590, 135, shadow2);
    painter.drawPixmap(595, 220, shadow3);
    painter.drawPixmap(600, 300, shadow4);
    painter.drawPixmap(50, 0, welcome);
}