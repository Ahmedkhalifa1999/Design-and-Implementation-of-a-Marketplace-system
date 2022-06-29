#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamanager.h"
#include <QPixmap>
#include <QMessageBox>
SignUpData sud;
SignUpResult sur;
DataManager dm;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerButton_clicked()
{
    sud.firstName = ui->fname->text();
    sud.lastName= ui->lname->text();
    sud.email = ui->email->text();
    sud.password = ui->password->text();
    sud.phone = ui->number->text();
    sud.address = ui->address->text();
    sur= dm.signUp(sud);

}


void MainWindow::on_loginButton_clicked()
{
   log = new Login(this);
   log->show();
}
void MainWindow:: signUp_slot(bool result){
    if (result){
        shop=new Shop(this);
        shop->show();
    }
    else{
        QMessageBox::warning(this,"Incorrect data","Try Again");
    }
}
