#include "cart.h"
#include "ui_cart.h"
#include "datamanager.h"
#include<QMessageBox>

Cart::Cart(DataManager *dataManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cart)
{
    this->dm = dataManager;
    QObject::connect(this->dm, &DataManager::checkout_signal, this, &Cart::checkout_slot);
    QObject::connect(this->dm, &DataManager::getCart_signal, this, &Cart::getCart_slot);
    ui-> setupUi(this);
    dm->getCart(); //Vector of detailed cart item


}

Cart::~Cart()
{
    delete ui;
}
void Cart :: getCart_slot (QVector <Item> result){
    for(int i =0;i<result.size();i++){
        dci[i].icon=result[i].icon;
        dci[i].ID=result[i].ID;
        dci[i].name=result[i].name;
        dci[i].price=result[i].price;
        //dci[i].quantity=result[i].quantity;
        dci[i].quantity = 0;
    }
    for(unsigned int i=0; i < dci.size();i++){

        id[i]=dci[i].ID;
        img[i]= dci[i].icon;
        names[i] =dci[i].name;
        prices[i]=dci[i].price;
        qu[i]=dci[i].quantity;
    }
    for(int i=0;i<img.size();i++){
        QLabel* pic = new QLabel(this);
        pic->setPixmap(img[i].scaled(100,100,Qt::KeepAspectRatio));
        imgl.push_back(pic);
        ui->gridLayout->addWidget(pic, i,0);
    }

    for(int i=0;i<names.size();i++){
        QLabel* nm = new QLabel(this);
        nm->setText(names[i]);
        namel.push_back(nm);
        ui->gridLayout->addWidget(nm, i,1);
    }


    for(int i=0;i<prices.size();i++){
        QLabel* pr = new QLabel(this);
        pr->setText(QString::number(prices[i].pounds)+"."+QString::number(prices[i].piasters));
        pricel.push_back(pr);
        ui->gridLayout->addWidget(pr, i,2);
    }
    for(int i=0;i<qu.size();i++){

        QLineEdit * quantity =new QLineEdit();
        quantity->setText(QString::number(qu[i]));
        vl.push_back(quantity);
        ui->gridLayout->addWidget(quantity, i,3);


    }
    for(int i=0;i<qu.size();i++){

        ButtonId *b = new ButtonId();
        b->setText("Remove");
        b->id = id[i];
        ui->gridLayout->addWidget(b, i,4);
        connect(b,SIGNAL(clicked()),this,SLOT(on_b_clicked()));

    }

}
void Cart::on_Checkout_clicked()
{
    dm->checkout();
    ui->Checkout->setEnabled(false);
}

void Cart:: checkout_slot(CheckoutResult result){

    if(result.unavailableItem==true){

        for(unsigned int j=0;j<result.itemAvailability.size();j++){
            if(result.itemAvailability[j].availableQuantity==0){
                unavailItem= result.itemAvailability[j].ID;
            }
        }
        QMessageBox:: warning(this,"Error", QString("Item of ID %1 is unavailable ") .arg(unavailItem));

    }          else if(result.notEnoughFunds==true)
        QMessageBox:: warning(this,"Error","There is no enough funds ");

    else{
        QMessageBox ::information(this,"Checkout is successful"," Your order is placed successfully");
    }
}


void Cart::on_b_clicked(){
    ButtonId* button = dynamic_cast<ButtonId *>(QObject::sender());
    for(int i =0;i<img.size();i++){
        if(button->id==id[i]){
            imgl[i]->hide();
            ui->gridLayout->removeWidget(imgl[i]);
            imgl.remove(i);
            namel[i]->hide();
            ui->gridLayout->removeWidget(namel[i]);
            namel.remove(i);
            pricel[i]->hide();
            ui->gridLayout->removeWidget(pricel[i]);
            pricel.remove(i);
            vl[i]->hide();
            ui->gridLayout->removeWidget(vl[i]);
            vl.remove(i);

        }
    }
}
void Cart::on_pushButton_clicked()

{    for(int i=0;i<qu.size();i++){

        upd[i].ID=dci[i].ID;
        upd[i].quantity= (vl[i]->text()).toUInt();
    }

     dm->updateCart(upd);
}
