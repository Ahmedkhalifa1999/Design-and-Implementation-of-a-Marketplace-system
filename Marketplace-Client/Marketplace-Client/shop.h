#ifndef SHOP_H
#define SHOP_H

#include <QDialog>
#include"datamanager.h"
#include "mainwindow.h"
#include "itemdet.h"
#include "cart.h"
#include "account.h"

namespace Ui {
class Shop;
}

class Shop : public QDialog
{
    Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop();

private slots:
    void on_but_clicked();
    void on_cartButton_clicked();

    void on_accountButton_clicked();

    void on_searchButton_clicked();

    void getCategories_slot(std::vector<QString> result);
    void getItemList_slot(std::vector<Item> result);

private:
    Ui::Shop *ui;
    DataManager *dm;
    Itemdet *item;
    Cart *cart;
    Account *acc;
};

#endif // SHOP_H