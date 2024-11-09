//
// Created by 戴显灏 on 11/8/24.
//

#ifndef PVZDIALOG_H
#define PVZDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <vector>
using namespace std;


class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class PVZDialogButton;

class PVZDialog : public QDialog {
    Q_OBJECT
public:
    explicit PVZDialog(QString title, QString message);
    void addButton(QString text, function<void()>clicked);
    void addAdditionalWidget(QWidget *widget);

private:
    int dialogWidth;
    int dialogHeight;
    const QString title;
    const QString message;

    QLabel *titleLabel;
    QLabel *messageLabel;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *buttonsLayout;
    vector<PVZDialogButton *>buttons;

    void setUpUI();
    void paintEvent(QPaintEvent *event) override;
    void setLayout(QLayout *);
};


#endif //PVZDIALOG_H
