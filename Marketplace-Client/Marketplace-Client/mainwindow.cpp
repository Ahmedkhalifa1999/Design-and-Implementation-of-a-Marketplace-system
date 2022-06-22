#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QPixmap logo(":/res/img/logo.png");
//    int w=ui->logoLabel->width();
//    int h=ui->logoLabel->height();

    //ui->logoLabel->setPixmap(logo.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerButton_clicked()
{
    QString fname = ui->fname->text();
    QString lname = ui->lname->text();
    QString email = ui->email->text();
    QString password = ui->password->text();
    QString number = ui->number->text();
    QString address = ui->address->text();

    //check the correctness if true connect to the DB and go to the home page if false show QMessageBox warning
}


void MainWindow::on_loginButton_clicked()
{
   log = new Login(this);
   log->show();
}

