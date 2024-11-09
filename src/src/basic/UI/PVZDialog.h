//
// Created by 戴显灏 on 11/8/24.
//

#ifndef PVZDIALOG_H
#define PVZDIALOG_H
#include <QDialog>
#include <QPushButton>


class QLabel;
class QHBoxLayout;

class PVZDialog : public QDialog {
    Q_OBJECT
public:
    explicit PVZDialog(QString title, QString message);
    void addButton(QString text, std::function<void()>clicked);

private:
    void paintEvent(QPaintEvent *event) override;

    int dialogWidth;
    int dialogHeight;

    QWidget *buttonsWidget;
};


#endif //PVZDIALOG_H
