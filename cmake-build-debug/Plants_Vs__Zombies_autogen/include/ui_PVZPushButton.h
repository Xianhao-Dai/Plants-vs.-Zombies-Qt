/********************************************************************************
** Form generated from reading UI file 'PVZPushButton.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVZPUSHBUTTON_H
#define UI_PVZPUSHBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PVZPushButton
{
public:

    void setupUi(QPushButton *PVZPushButton)
    {
        if (PVZPushButton->objectName().isEmpty())
            PVZPushButton->setObjectName("PVZPushButton");
        PVZPushButton->resize(400, 300);

        retranslateUi(PVZPushButton);

        QMetaObject::connectSlotsByName(PVZPushButton);
    } // setupUi

    void retranslateUi(QPushButton *PVZPushButton)
    {
        PVZPushButton->setWindowTitle(QCoreApplication::translate("PVZPushButton", "PVZPushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PVZPushButton: public Ui_PVZPushButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVZPUSHBUTTON_H
