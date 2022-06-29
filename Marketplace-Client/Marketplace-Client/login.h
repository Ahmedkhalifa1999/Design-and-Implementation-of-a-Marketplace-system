#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "shop.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_logButton_clicked();

    void on_regButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::Login *ui;
    Shop *shop;
};

#endif // LOGIN_H
