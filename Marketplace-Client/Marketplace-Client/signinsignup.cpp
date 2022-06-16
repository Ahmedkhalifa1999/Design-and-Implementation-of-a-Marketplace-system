#include "signinsignup.h"
#include "ui_signinsignup.h"

SignInSignUp::SignInSignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInSignUp)
{
    ui->setupUi(this);
}

SignInSignUp::~SignInSignUp()
{
    delete ui;
}
