#ifndef SHOP_H
#define SHOP_H

#include <QDialog>
#include"datamanager.h"
//#include "mainwindow.h"
#include "itemdet.h"
#include "cart.h"
#include "account.h"
#include "buttonid.h"

namespace Ui {
class Shop;
}

class Shop : public QDialog
{
    Q_OBJECT
    QList <QString> myList;
    SearchQuery sq;
    QVector <QPixmap> img;
    QVector <QString> names;
    QVector <MoneyAmount> prices;
    QVector <unsigned int> ids;
    QString search;
    QVector <int> butid;
    ButtonId *button;

public:
    explicit Shop(DataManager *dataManager, QWidget *parent = nullptr);
    ~Shop();
    //ButtonId *button;


private slots:
    void on_b_clicked();
    void on_cartButton_clicked();

    void on_accountButton_clicked();

    void on_searchButton_clicked();

public slots:

    void getCategories_slot(QVector<QString> result);
    void getItemList_slot(QVector<Item> result);

private:
    Ui::Shop *ui;
    DataManager *dm;
    Itemdet *itemd;
    Cart *cart;
    Account *acc;
    //ButtonId *b;
    //ButtonId *button;

};

#endif // SHOP_H
