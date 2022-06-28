#ifndef SHOP_H
#define SHOP_H

#include <QDialog>
#include"datamanager.h"
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
    void on_cartButton_clicked();

    void on_accountButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::Shop *ui;
    DataManager *dm;
};

#endif // SHOP_H
