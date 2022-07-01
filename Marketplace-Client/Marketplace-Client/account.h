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
    DataManager *dm;
    AccountDetails ad,details;
    MoneyAmount wal;
    UpdateAccountResult uar;
    QVector<unsigned int> ids;
    QVector<OrderState> states;
    unsigned int orderid;
    QVector<MoneyAmount> amounts;
    QVector<unsigned int> itemid;
    QVector<QPixmap> itempic;
    QVector<QString> itemname;
    QVector<MoneyAmount> itemprice;
    QVector<unsigned int> itemquant;

public:
    explicit Account(DataManager* dataManager, QWidget *parent = nullptr);
    ~Account();

private slots:
    void on_butt_clicked();

    void on_save_clicked();

    void on_phone_editingFinished();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_deposit_clicked();

    void on_name_editingFinished();

    void walletDeposit(MoneyAmount amount);

public slots:

    void getAccountDetails_slot(AccountDetails result);

    void updateAccountDetails_slot(bool result);

    void walletDeposit_slot(bool result);

    void getOrderHistory_slot(QVector<OrderSummary> result);

    void getOrderDetails_slot(DetailedOrder result);

private:
    Ui::Account *ui;
    Cart *cart ;
    QString enumtostring(OrderState os);
};

#endif // ACCOUNT_H
