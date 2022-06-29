#include "cart.h"
#include "ui_cart.h"
#include "datamanager.h"
#include <vector>
DataManager dm;
std::vector <DetailedCartItem> dci;
QVector< unsigned int>qu;
QVector <QPixmap> img;
QVector <QString> names;
QVector <MoneyAmount> prices;
Cart::Cart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);
    dci= dm.getCart(); //Vector of detailed cart item
    for(unsigned int i=0; i < dci.size();i++){
        img[i]=dci[i].icon();
         names[i] =dci[i].name;
         prices[i]=dci[i].price;
         qu[i]=dci[i].quantity;
    }
    for(int i=0;i<img.size();i++){
       QLabel* pic = new QLabel(this);
         pic->setPixmap(img[i].scaled(110,110,Qt::KeepAspectRatio));
         ui->gridLayout->addWidget(pic, i,0);
    }

    for(int i=0;i<names.size();i++){
       QLabel* nm = new QLabel(this);
         nm->setText(names[i]);
         ui->gridLayout->addWidget(nm, i,1);
    }

    for(int i=0;i<prices.size();i++){
       QLabel* pr = new QLabel(this);
         pr->setText(QString::number(prices[i].pounds)+"."+QString::number(prices[i].piasters));
         ui->gridLayout->addWidget(pr, i,2);
    }
    for(int i=0;i<qu.size();i++){
        if(qu[i]==0){
            continue;
        }
       QLabel* quantity = new QLabel(this);
         quantity->setText(QString::number(qu[i]));
         ui->gridLayout->addWidget(quantity, i,2);
    }

}

Cart::~Cart()
{
    delete ui;
}

void Cart::on_Checkout_clicked()
{
dm.checkout();
}

void updateCart(std::vector<CartItem> updated){
    for(unsigned int i =0;i < dci.size();i++){
        if(updated[i].ID == dci[i].ID){
            dci[i].quantity=updated[i].quantity;
        }
    }

}

void Cart::on_pushButton_clicked()
{
dm.updateCart();
}

