#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
#include "cart.h"
#include "datamanager.h"
namespace Ui {
class Account;
}

class Account : public QDialog
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();

private slots:
    void on_save_clicked();

    void on_address_editingFinished();

    void on_phone_editingFinished();

    void walletDeposit(MoneyAmount amount);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void getAccountDetails_slot(AccountDetails result);

    void updateAccountDetails_slot(bool result);

    void on_deposit_clicked();

    void walletDeposit_slot(bool result);

    void getOrderHistory_slot(std::vector<OrderSummary> result);

    void on_orderDetail_clicked();

    void getOrderDetails_slot(DetailedOrder result);

    void on_name_editingFinished();

private:
    Ui::Account *ui;
    Cart *cart ;
    QString enumtostring(OrderState os);
};

#endif // ACCOUNT_H
