#ifndef ITEMDET_H
#define ITEMDET_H

#include <QDialog>
#include"datamanager.h"
//#include "shop.h"

namespace Ui {
class Itemdet;
}

class Itemdet : public QDialog
{
    Q_OBJECT
    QString item_name;
    QString item_description;
    QVector<QPixmap> item_images;
    MoneyAmount item_price;
    unsigned int quan;
    CartItem c;

public:
    explicit Itemdet(DataManager *dataManager, unsigned int ID, QWidget *parent = nullptr);
    ~Itemdet();

private slots:
    void on_shopButton_clicked();
    void on_addCartButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

public slots:
    void getItemData_slot(DetailedItem result);

private:
    Ui::Itemdet *ui;
    DataManager *dm;
    //Shop *s;
};

#endif // ITEMDET_H
