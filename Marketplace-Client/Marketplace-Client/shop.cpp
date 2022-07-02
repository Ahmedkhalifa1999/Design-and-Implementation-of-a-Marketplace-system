#include "shop.h"
#include "ui_shop.h"
#include "datamanager.h"

#include "buttonid.h"


Shop::Shop(DataManager *dataManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shop)
{
    this->dm = dataManager;
    QObject::connect(this->dm, &DataManager::getCategories_signal, this, &Shop::getCategories_slot);
    QObject::connect(this->dm, &DataManager::getItemList_signal, this, &Shop::getItemList_slot);
    ui->setupUi(this);
    dm->getCategories();

}

Shop::~Shop()
{
    delete ui;
}
void Shop::on_b_clicked()
{
//  QObject* obj = sender();
//  obj = qobject_cast<QObject *>(b);
  button = dynamic_cast<ButtonId *>(QObject::sender());

  itemd = new Itemdet(this->dm, button->id, this);
  itemd->show();

}

void Shop::on_cartButton_clicked()
{
 cart = new Cart(this->dm, this);
 cart->show();
}


void Shop::on_accountButton_clicked()
{
  acc = new Account(this->dm, this);
  acc->show();
}


void Shop::on_searchButton_clicked()
{
 search = ui->search_lineEdit->text();
 //sq.name=search;
 //dm->getItemList(sq);

}
void Shop::getCategories_slot(QVector<QString> result){

    for(int i=0; i < result.size(); i++){
        myList.push_back(result[i]);
    }
    ui->listWidget->addItems(myList);
    sq.name = search;
    sq.categories = myList;
    sq.maxResults = 10;
    dm->getItemList(sq);

}

void Shop::getItemList_slot(QVector<Item> result){
    for(int i=0; i < result.size();i++){
        img.push_back(result[i].icon);
        names.push_back(result[i].name);
        prices.push_back(result[i].price);
        ids.push_back(result[i].ID);
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

    for(int i=0;i<ids.size();i++){

        ButtonId *b = new ButtonId();
        b->setText("View an item");
        b->id = ids[i];
        ui->gridLayout->addWidget(b, i,3);
        connect(b,SIGNAL(clicked()),this,SLOT(on_b_clicked()));
         //QPushButton* but = new QPushButton("view an item");


    }

}
