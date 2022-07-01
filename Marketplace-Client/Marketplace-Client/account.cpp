//#include "account.h"
//#include"cart.h"
#include"datamanager.h"
#include "ui_account.h"
#include  "shop.h"
#include<QMessageBox>
#include<QMetaEnum>


Account::Account(DataManager *dataManager, QWidget *parent) :
    QDialog(parent),

    ui(new Ui::Account)
{
    this->dm = dataManager;
    QObject::connect(this->dm, &DataManager::getAccountDetails_signal, this, &Account::getAccountDetails_slot);
    QObject::connect(this->dm, &DataManager::updateAccountDetails_signal, this, &Account::updateAccountDetails_slot);
    QObject::connect(this->dm, &DataManager::walletDeposit_signal, this, &Account::walletDeposit_slot);
    QObject::connect(this->dm, &DataManager::getOrderHistory_signal, this, &Account::getOrderHistory_slot);
    QObject::connect(this->dm, &DataManager::getOrderDetails_signal, this, &Account::getOrderDetails_slot);
    ui->setupUi(this);
    dm->getAccountDetails();
    ui->name->insert(ad.name);
    ui->email->insert(ad.email);
    ui->email->setEnabled(false);
    ui->phone->insert(ad.phone);
    ui->address->insert(ad.address);
    ui->balance->setText((QString::number(ad.wallet.pounds)+"."+QString::number(ad.wallet.piasters)));

    dm->getOrderHistory();

    for(int i=0;i<ids.size();i++){
       QLabel* idl = new QLabel(this);
         idl->setText(QString::number(ids[i]));
         ui->gridLayout_3->addWidget(idl, i,0);
    }

    for(int i=0;i<states.size();i++){
       QLabel* st = new QLabel(this);
          QString stat = enumtostring(states[i]);
         st->setText(stat);
         ui->gridLayout_3->addWidget(st, i,1);
    }

    for(int i=0;i<amounts.size();i++){
       QLabel* pr = new QLabel(this);
         pr->setText(QString::number(amounts[i].pounds)+"."+QString::number(amounts[i].piasters));
         ui->gridLayout_3->addWidget(pr, i,2);
    }

    for(int i=0;i<ids.size();i++){
        ButtonId *b = new ButtonId();
        b->setText("View Order");
        b->id = ids[i];
        ui->gridLayout_3->addWidget(b, i,3);
        connect(b,SIGNAL(clicked()),this,SLOT(on_butt_clicked()));

    }

    for(int i=0;i<itemid.size();i++){
       QLabel* it = new QLabel(this);
         it->setText(QString::number(itemid[i]));
         ui->gridLayout_4->addWidget(it, i,0);
    }

    for(int i=0;i<itempic.size();i++){
       QLabel* p = new QLabel(this);
         p->setPixmap(itempic[i].scaled(100,100,Qt::KeepAspectRatio));
         ui->gridLayout_4->addWidget(p, i,1);
    }

    for(int i=0;i<itemname.size();i++){
       QLabel* in = new QLabel(this);
         in->setText(itemname[i]);
         ui->gridLayout_4->addWidget(in, i,2);
    }

    for(int i=0;i<itemprice.size();i++){
       QLabel* ip = new QLabel(this);
         ip->setText(QString::number(itemprice[i].pounds)+"."+QString::number(itemprice[i].piasters));
         ui->gridLayout_4->addWidget(ip, i,3);
    }

    for(int i=0;i<itemquant.size();i++){
       QLabel* iq = new QLabel(this);
         iq->setText(QString::number(itemquant[i]));
         ui->gridLayout_4->addWidget(iq, i,4);
    }





}

Account::~Account()
{
    delete ui;
}
void Account::on_butt_clicked()
{
//  QObject* obj = sender();
//  obj = qobject_cast<QObject *>(b);
  ButtonId *button = dynamic_cast<ButtonId *>(QObject::sender());
  orderid = button->id;
  dm->getOrderDetails(orderid);


}
void Account::getAccountDetails_slot(AccountDetails result){

    ad.name=result.name;

    ad.phone=result.phone;
    ad.email = result.email;
    ad.address= result.address;
    ad.wallet = result.wallet;

}

void Account::on_save_clicked()
{
  uar= dm->updateAccountDetails(ad);
  if(uar.validEmail == false){
     QMessageBox::warning(this,"Error","Invalid Email so please try again");
 }
  else if(uar.validPhone == false){
      QMessageBox::warning(this,"Error","Invalid Phone number so please try again");
  }


}

void Account::on_name_editingFinished()
{
    ad.name= ui->name->text();
}




void Account::on_phone_editingFinished()
{
    ad.phone = ui->phone->text();
}
void Account::updateAccountDetails_slot(bool result){
    if(result){
        QMessageBox::information(this,"updated","Information is updated successfully");
    }
    else {
        QMessageBox::warning(this,"Error","It can't be updated");
    }
}

void Account::on_pushButton_clicked() //go to home page
{
    hide();

}

void Account::walletDeposit(MoneyAmount amount){
    ad.wallet.pounds =amount.pounds;
    ad.wallet.piasters=amount.piasters;
}


void Account::on_pushButton_2_clicked() //go to cart page
{
    cart = new Cart(this->dm, this);
    cart -> show();
}


void Account::on_deposit_clicked()
{
    wal.pounds= (ui->poundLine->text()).toUInt();
    wal.piasters= (ui->piasterLine->text()).toUInt();
    dm->walletDeposit(wal);
}

void Account::walletDeposit_slot(bool result){
    if(result){
        QMessageBox::information(this,"Deposit","The Deposit operation is done correctly");

    }
    else
        QMessageBox::warning(this,"Error","The Deposit operation is not done");
}

void Account::getOrderHistory_slot(QVector<OrderSummary> result){

    for(int i=0;i<result.size();i++){
        ids[i]=result[i].ID;
        states[i]=result[i].state;
        amounts[i]=result[i].totalAmount;
    }



}


void Account::getOrderDetails_slot(DetailedOrder result){
    for(int i=0;i<result.items.size();i++){

        itemid[i]=result.items[i].ID;
        itempic[i]=result.items[i].icon;
        itemname[i]=result.items[i].name;
        itemprice[i]=result.items[i].price;
        itemquant[i]=result.items[i].quantity;

    }
}
QString Account::enumtostring(OrderState os){
    if(os==OrderState::ACCEPTED)
        return "ACCEPTED";
    else if(os==OrderState::REJECTED)
        return "REJECTED";
   else if(os==OrderState::SHIPPED)
        return "SHIPPED";
    else if(os==OrderState::SHIPPING)
        return "SHIPPING";
    return "REJECTED";
}




