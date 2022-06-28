#include "item.h"
#include "ui_item.h"

Item::Item(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);
}

Item::~Item()
{
    delete ui;
}
