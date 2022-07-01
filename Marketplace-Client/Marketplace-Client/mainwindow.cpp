#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamanager.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(DataManager *dataManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->dm = dataManager;
    QObject::connect(this->dm, &DataManager::signUp_signal, this, &MainWindow::signUp_slot);
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerButton_clicked()
{
    sud.name = ui->name->text();

    sud.email = ui->email->text();
    sud.password = ui->password->text();
    sud.phone = ui->number->text();
    sud.address = ui->address->text();
    sur= dm->signUp(sud);

    if(sur.validEmail==false && sur.validPhone==false){
        QMessageBox::warning(this,"Error","Incorrect Email and phone, please try Again");
    }
    else if (sur.validEmail==false){
        QMessageBox::warning(this,"Error","Incorrect Email, Please try Again");
    }else if(sur.validPhone==false){
         QMessageBox::warning(this,"Error","Incorrect Phone, Please try Again");
    }

}


void MainWindow::on_loginButton_clicked()
{
   log = new Login(this->dm, this);
   log->show();
}
void MainWindow:: signUp_slot(bool result){
    if (result == true){ //The signup is successful the user does not exist
        shop = new Shop(this->dm, this);
        shop->show();
    }
    else {
        QMessageBox::warning(this,"Error","User already exists, Please try Again");
    }
}
