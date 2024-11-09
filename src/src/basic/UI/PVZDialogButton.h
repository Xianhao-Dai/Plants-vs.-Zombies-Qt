//
// Created by 戴显灏 on 11/9/24.
//

#ifndef PVZDIALOGBUTTON_H
#define PVZDIALOGBUTTON_H

#include <QPushButton>

class QLabel;

class PVZDialogButton : public QPushButton {
    Q_OBJECT
public:
    explicit PVZDialogButton(QWidget *parent, QString text);
private:
    QPixmap icon;
    QPixmap highlightedIcon;
    QLabel *textLabel;

    int buttonWidth;
    int buttonHeight;
};



#endif //PVZDIALOGBUTTON_H
