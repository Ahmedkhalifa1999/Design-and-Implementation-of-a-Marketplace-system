#include "account.h"
#include"cart.h"
#include"datamanager.h"
#include "ui_account.h"
#include  "shop.h"
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
    ad.firstName = ui->fname->text();
    ad.lastName= ui->lname->text();
    ad.email = ui->email->text();
    ad.phone = ui->phone->text();
    ad.address = ui->address->text();
  //  ad.wallet = ui->balance->text();
}

Account::~Account()
{
    delete ui;
}

void getAccountDetails_slot(AccountDetails result){
    ad=result;
}

void Account::on_save_clicked()
{
  up= dm.updateAccountDetails(ad);
}


void Account::on_fname_editingFinished()
{
    ad.firstName=ui->fname->text();
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

/*
void Account::on_balance_editingFinished()
{
    details.wallet= setText(QString::number(balance.pounds));
        details.wallet.pounds = ui->balance->text();
}

*/
void Account::on_pushButton_clicked() //go to home page
{
    shop = new Shop(this);
    shop -> show();
}


void Account::on_pushButton_2_clicked() //go to cart page
{
    cart = new Cart(this);
    cart -> show();
}

