#include "account.h"
#include"cart.h"
#include"datamanager.h"
#include "ui_account.h"
<<<<<<< Updated upstream
#include  "shop.h"
#include<QMessageBox>
=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    ui->fname->insert(ad.firstName);
    ui->lname->insert(ad.lastName);
    ui->email->insert(ad.email);
    ui->phone->insert(ad.phone);
    ui->address->insert(ad.address);
    ui->balance->insert(QString::number(ad.wallet.pounds)+"."+QString::number(ad.wallet.piasters));

=======
    ui->fname->insert( ad.firstName) ;
    ui->lname->insert(ad.lastName);
    ui->email->insert(ad.email) ;
    ui->phone->insert(ad.phone) ;
    ui->address->insert(ad.address) ;
    ui->balance->setText((QString::number(ad.wallet.pounds)+"."+QString::number(ad.wallet.piasters)));
>>>>>>> Stashed changes
}

Account::~Account()
{
    delete ui;
}

<<<<<<< Updated upstream
void Account::getAccountDetails_slot(AccountDetails result){

    ad.firstName=result.firstName;
    ad.lastName=result.lastName;
    ad.phone=result.phone;
    ad.email = result.email;
    ad.address= result.address;
    ad.wallet = result.wallet;
=======
void getAccountDetails_slot(AccountDetails result){
    ad.firstName=result.firstName;
    ad.lastName=result.lastName;
    ad.address=result.address;
    ad.email=result.email;
    ad.phone=result.phone;
    ad.wallet=result.wallet;
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
    }
}

void Account::on_pushButton_clicked() //go to home page
{
    shop = new Shop(this);
    shop->show();
=======

void walletDeposit(MoneyAmount amount){
    ad.wallet.pounds =amount.pounds;
    ad.wallet.piasters=amount.piasters;
}



void Account::on_pushButton_clicked() //go to home page
{
    hide();
>>>>>>> Stashed changes
}


void Account::on_pushButton_2_clicked() //go to cart page
{
    cart = new Cart(this);
    cart -> show();
}

