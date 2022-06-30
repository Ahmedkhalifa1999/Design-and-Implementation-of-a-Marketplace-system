#include "shop.h"
#include "ui_shop.h"
#include "datamanager.h"

#include "buttonid.h"
QList <QString> myList;
SearchQuery sq;
QVector <QPixmap> img;
QVector <QString> names;
QVector <MoneyAmount> prices;
QVector <unsigned int> ids;
QString search;
QVector <int> butid;


Shop::Shop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    dm->getCategories();
    ui->listWidget->addItems(myList);
    sq.name = search;
    sq.categories[0] = ui->listWidget->currentItem()->text();
    sq.maxResults = 10;
    dm->getItemList(sq);

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

         //QPushButton* but = new QPushButton("view an item");


    }



}

Shop::~Shop()
{
    delete ui;
}
void Shop::on_b_clicked()
{
//  QObject* obj = sender();
//  obj = qobject_cast<QObject *>(b);
  button = qobject_cast<ButtonId *>(QObject::sender());

  itemd = new Itemdet(this);
  itemd->show();

}

void Shop::on_cartButton_clicked()
{
 cart = new Cart(this);
 cart->show();
}


void Shop::on_accountButton_clicked()
{
  acc = new Account(this);
  acc->show();
}


void Shop::on_searchButton_clicked()
{
 search = ui->search_lineEdit->text();
 //sq.name=search;
 //dm->getItemList(sq);

}
void Shop::getCategories_slot(std::vector<QString> result){

    for(int i=0; i < result.size(); i++){
        myList.push_back(result[i]);
    }

}

void getItemList_slot(std::vector<Item> result){
    for(int i=0; i < result.size();i++){
        img[i]=result[i].icon();
         names[i] =result[i].name;
         prices[i]=result[i].price;
         ids[i]=result[i].ID;
    }

}
