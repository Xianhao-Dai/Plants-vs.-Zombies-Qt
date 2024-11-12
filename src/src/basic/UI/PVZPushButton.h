//
// Created by 戴显灏 on 11/7/24.
//

#ifndef PVZPUSHBUTTON_H
#define PVZPUSHBUTTON_H

#include "src/src/game_widget/PVZGameStartWidget.h"

#include <QPushButton>

class PVZPushButton : public QPushButton {
    Q_OBJECT
public:
    explicit PVZPushButton(QWidget *parent, QString iconPath, QString highlightIconPath = "");
    void setText(const QString &text);
    void setFont(const QFont &font);

protected:
    QLabel *textLabel;

    QString iconPath;
    QString highlightedIconPath;
    QPixmap icon;
    QPixmap highlightedIcon;
};



#endif //PVZPUSHBUTTON_H
