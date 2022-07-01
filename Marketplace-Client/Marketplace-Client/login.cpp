#include "login.h"
#include "ui_login.h"
#include"datamanager.h"
#include <QPixmap>
#include <QMessageBox>
//#include "shop.h"

Login::Login(DataManager *dataManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    this->dm = dataManager;
    QObject::connect(this->dm, &DataManager::signIn_signal, this, &Login::signIn_slot);
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
 save = ui->checkBox->isChecked(); //if the user want to be rememberd or not
 flag = dm->signIn(sid,save);

  if(flag==false){
   QMessageBox::warning(this,"Error ","Invalid Email, Please try Again");
  }

}


void Login::on_regButton_clicked()
{
 hide();
}


void Login::signIn_slot(bool result){

    if (result == true){  //The signin is successful the user put right credentials
        shop = new Shop(this->dm, this);
        shop->show();
    }
    else {
        QMessageBox::warning(this,"Error","Invalid Email or Password,Please try Again");
    }
}

