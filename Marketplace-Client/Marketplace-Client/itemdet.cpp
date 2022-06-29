#include "itemdet.h"
#include "ui_itemdet.h"

Itemdet::Itemdet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Itemdet)
{
    ui->setupUi(this);
}

Itemdet::~Itemdet()
{
    delete ui;
}
