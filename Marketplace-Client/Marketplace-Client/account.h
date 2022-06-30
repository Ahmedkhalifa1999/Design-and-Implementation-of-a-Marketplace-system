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

    void on_fname_editingFinished();

    void on_lname_editingFinished();

    void on_email_editingFinished();

    void on_address_editingFinished();

    void on_phone_editingFinished();

    void walletDeposit(MoneyAmount amount);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void getAccountDetails_slot(AccountDetails result);

    void updateAccountDetails_slot(bool result);

private:
    Ui::Account *ui;
    Cart *cart ;
};

#endif // ACCOUNT_H
