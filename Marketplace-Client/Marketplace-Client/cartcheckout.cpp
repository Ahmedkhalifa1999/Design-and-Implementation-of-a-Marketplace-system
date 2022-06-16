#include "cartcheckout.h"
#include "ui_cartcheckout.h"

CartCheckout::CartCheckout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartCheckout)
{
    ui->setupUi(this);
}

CartCheckout::~CartCheckout()
{
    delete ui;
}
