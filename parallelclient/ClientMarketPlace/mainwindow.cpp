#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QString username= ui->username->text();
    QString email= ui->email->text();
    QString password= ui->password->text();
    QString address= ui->address->text();

    //check the correctness if correct go to shop page if not QmessageBox of type warning
}


void MainWindow::on_loginButton_clicked()
{
     log = new Login(this);
     log->show();
}

