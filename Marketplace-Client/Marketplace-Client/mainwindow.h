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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_registerButton_clicked();

    void on_loginButton_clicked();

public slots:
    //Sign-in & sign-up signals
    void signUp_slot(bool result);
    void signIn_slot(bool result);

    //Cart-related signals
    void checkout_slot(bool result, std::vector<CheckoutResult> detailedResult);
    void  getCart_slot (QVector <DetailedCartItem> result);
    //Account-related signals
    void getAccountDetails_slot(AccountDetails result);
    void updateAccountDetails_slot(bool result);
    void getOrderHistory_slot(std::vector<OrderSummary> result);
    void getOrderDetails_slot(DetailedOrder result);
    void walletDeposit_slot(bool result);

    //Shop-related signals
    void getItemList_slot(std::vector<Item> result);
    void getItemData_slot(DetailedItem result);
    void getCategories_slot(std::vector<QString> result);

private:
    Ui::MainWindow *ui;
    Login *log;
    Shop *shop;
};
#endif // MAINWINDOW_H
