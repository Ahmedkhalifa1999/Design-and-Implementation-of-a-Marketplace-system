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

    SignInData sid;
    DataManager *dm;
    bool flag,save;

public:
    explicit Login(DataManager *dataManager, QWidget *parent = nullptr);
    ~Login();

private slots:

    void on_logButton_clicked();

    void on_regButton_clicked();



public slots:

    void signIn_slot(bool result);

private:
    Ui::Login *ui;
    Shop *shop;
};

#endif // LOGIN_H
