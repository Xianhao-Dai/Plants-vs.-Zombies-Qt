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
#include <QTimer>

#include "src/src/adventure/PVZAdventureController.h"
#include "src/src/basic/util/PVZGameInfoUtil.h"

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
    startAdventureButton->move(399, 62);
    connect(startAdventureButton, &PVZPushButton::clicked, [=]() {
        QTimer::singleShot(100, [=]() {
            this->hide();
            PVZAdventureController *adventureController = new PVZAdventureController();
            adventureController->runAdventure();
        });
    });

    miniGamesButton = new PVZPushButton(this, "/bg/menu_mini_games");
    miniGamesButton->move(405, 171);
    puzzleButton = new PVZPushButton(this, "/bg/menu_puzzle");
    puzzleButton->move(413, 256);
    survivalButton = new PVZPushButton(this, "/bg/menu_survival");
    survivalButton->move(412, 328);
    changeNameButton = new PVZPushButton(this, "/bg/menu_change_name");
    changeNameButton->move(50, 135);
    changeNameDialog = new PVZDialog("Change Your Name", "You may change your name if it's not your account!");
    changeNameDialog->addButton("Confirm", [=]() {
        changeNameDialog->hide();
        if (!nameLineEdit->text().isEmpty()) {
            nameLabel->setText(nameLineEdit->text());
            PVZGameInfoUtil::setUserName(nameLineEdit->text());
        }
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
    nameLabel = new QLabel(this);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setFixedSize(225, 20);
    nameLabel->move(85, 95);
    nameLabel->setFont(QFont("Chalkduster", 15, QFont::Light));
    nameLabel->setStyleSheet("color: rgb(255, 255, 255); background-color: transparent;");
    nameLabel->setText(PVZGameInfoUtil::getUserName());
}

void PVZMenuWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap sky = PVZResourceLoaderUtil::loadFullWindowPixmap("/bg/menu_sky.jpg");
    QPixmap tree = PVZResourceLoaderUtil::loadScaledPixmap("/bg/menu_tree.png", 0, mainWindowHeight, Qt::KeepAspectRatio);
    QPixmap tomb = PVZResourceLoaderUtil::loadScaledPixmap("/bg/menu_tomb.png", 0, mainWindowHeight - 40, Qt::KeepAspectRatio);
    QPixmap ground = PVZResourceLoaderUtil::loadPixmap("/bg/menu_ground.png");
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
    painter.drawPixmap(0, mainWindowHeight - tree.height(), tree);
    painter.drawPixmap(mainWindowWidth - tomb.width(), mainWindowHeight - tomb.height(), tomb);
    painter.drawPixmap(399, 62, shadow1);
    painter.drawPixmap(405, 171, shadow2);
    painter.drawPixmap(413, 256, shadow3);
    painter.drawPixmap(412, 328, shadow4);
    painter.drawPixmap(50, 0, welcome);
}