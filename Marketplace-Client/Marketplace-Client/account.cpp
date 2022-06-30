#include "account.h"
#include"cart.h"
#include"datamanager.h"
#include "ui_account.h"
#include  "shop.h"
#include<QMessageBox>
DataManager dm;
AccountDetails ad,details;
MoneyAmount wal;
bool up;
Account::Account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
    dm.getAccountDetails();
    ui->fname->insert(ad.firstName);
    ui->lname->insert(ad.lastName);
    ui->email->insert(ad.email);
    ui->phone->insert(ad.phone);
    ui->address->insert(ad.address);
    ui->balance->insert(QString::number(ad.wallet.pounds)+"."+QString::number(ad.wallet.piasters));

}

Account::~Account()
{
    delete ui;
}

void Account::getAccountDetails_slot(AccountDetails result){

    ad.firstName=result.firstName;
    ad.lastName=result.lastName;
    ad.phone=result.phone;
    ad.email = result.email;
    ad.address= result.address;
    ad.wallet = result.wallet;

}

void Account::on_save_clicked()
{
  up= dm.updateAccountDetails(ad);
  if(!up){
      QMessageBox::warning(this,"Error","Invalid Email or Phone number so please try again");
  }

}


void Account::on_fname_editingFinished()
{
    ad.firstName = ui->fname->text();
}


void Account::on_lname_editingFinished()
{
    ad.lastName=ui->lname->text();
}


void Account::on_email_editingFinished()
{

    ad.email = ui->email->text();
}


void Account::on_address_editingFinished()
{
    ad.address = ui->address->text();
}


void Account::on_phone_editingFinished()
{
    ad.phone = ui->phone->text();
}
void updateAccountDetails_slot(bool result){
    if(result){

    }
}

void Account::on_pushButton_clicked() //go to home page
{
    shop = new Shop(this);
    shop->show();
}


void Account::on_pushButton_2_clicked() //go to cart page
{
    cart = new Cart(this);
    cart -> show();
}

