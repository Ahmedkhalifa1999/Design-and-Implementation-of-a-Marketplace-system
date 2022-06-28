#include "shop.h"
#include "ui_shop.h"
#include "datamanager.h"

Shop::Shop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    dm = new DataManager(this);
    dm->getCategories();
    QList<QString> myList = QList<QString>::fromVector(QVector<QString>::fromVector(result));
    ui->listWidget->addItems(myList);
    SearchQuery sq;
    sq.categories = result;
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

