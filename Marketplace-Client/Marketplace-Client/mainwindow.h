#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datamanager.h"

#include <QMainWindow>
#include "login.h"
#include "shop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    SignUpData sud;
    SignUpResult sur;
    DataManager *dm;

public:
    MainWindow(DataManager *dataManager, QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_registerButton_clicked();

    void on_loginButton_clicked();

public slots:
    void signUp_slot(bool result);

private:
    Ui::MainWindow *ui;
    Login *log;
    Shop *shop;
};
#endif // MAINWINDOW_H
