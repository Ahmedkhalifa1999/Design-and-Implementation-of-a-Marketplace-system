#include "login.h"
#include "ui_login.h"
#include"datamanager.h"
#include <QPixmap>
#include <QMessageBox>
#include "shop.h"
AutoSignInResult asir;
SignInData sid;
DataManager dm;
bool log,save;
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

void Login::on_logButton_clicked()
{
 sid.email = ui->emailLog->text();
 sid.password = ui->passLog->text();
 save= ui->checkBox->isChecked(); //if the user want to be rememberd or not
 log=dm.signIn(sid,save);

  if(log==false){
   QMessageBox::warning(this,"Invalid Email ","Please try Again");
  }
 //check from the DB if correct go to home if not QMessageBox warning
 //


}


void Login::on_regButton_clicked()
{
 hide();
}


AutoSignInResult autoSignIn(){

}


void signIn_slot(bool result){

    if (result == true){  //The signin is successful the user put right credentials
        shop = new Shop(this);
        shop ->show();
    }
    else {
        QMessageBox::warning(this,"Ivalid Email or Password","Please try Again");
    }
}

