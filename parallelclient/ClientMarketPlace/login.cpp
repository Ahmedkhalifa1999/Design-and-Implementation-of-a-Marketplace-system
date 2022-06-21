#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    QString username= ui->userlineEdit->text();
    QString password= ui->passlineEdit->text();
    //check correctnes if right go to home page else QMessageBox warning

}


void Login::on_registerButton_clicked()
{
    hide();
}

