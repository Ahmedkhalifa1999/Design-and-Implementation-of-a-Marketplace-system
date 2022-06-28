#include "shop.h"
#include "ui_shop.h"
#include "datamanager.h"
QList <QString> myList;
SearchQuery sq;


Shop::Shop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    dm->getCategories();
    ui->listWidget->addItems(myList);
    sq.categories[0] = ui->listWidget->currentItem()->text();
    sq.maxResults = 10;
    dm->getItemList(sq);

}

Shop::~Shop()
{
    delete ui;
}

void Shop::on_cartButton_clicked()
{

}


void Shop::on_accountButton_clicked()
{

}


void Shop::on_searchButton_clicked()
{

}
void Shop::getCategories_slot(std::vector<QString> result){

    for(int i=0; i < result.size(); i++){
        myList.push_back(result[i]);
    }

}

void getItemList_slot(std::vector<Item> result){
    for(int i=0; i < result.size();i++)
}
