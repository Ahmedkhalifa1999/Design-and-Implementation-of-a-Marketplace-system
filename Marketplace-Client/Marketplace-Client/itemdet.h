#ifndef ITEMDET_H
#define ITEMDET_H

#include <QDialog>
#include"datamanager.h"
#include "shop.h"

namespace Ui {
class Itemdet;
}

class Itemdet : public QDialog
{
    Q_OBJECT

public:
    explicit Itemdet(QWidget *parent = nullptr);
    ~Itemdet();

private slots:
    void on_shopButton_clicked();
    void getItemData_slot(DetailedItem result);
    void on_addCartButton_clicked();

private:
    Ui::Itemdet *ui;
    DataManager *dm;
    Shop *s;
};

#endif // ITEMDET_H
