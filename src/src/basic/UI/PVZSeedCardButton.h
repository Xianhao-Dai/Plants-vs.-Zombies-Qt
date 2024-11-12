//
// Created by 戴显灏 on 11/10/24.
//

#ifndef PVZSEEDCARDBUTTON_H
#define PVZSEEDCARDBUTTON_H
#include "PVZPushButton.h"

class PVZSeedCardButton : public PVZPushButton {
    Q_OBJECT
public:
    explicit PVZSeedCardButton(QString id, QSize size, bool enabled=true, QWidget *parent=0);
};



#endif //PVZSEEDCARDBUTTON_H
