#ifndef CART_H
#define CART_H
#include<QLabel>
#include <QDialog>
#include <QLineEdit>
#include"datamanager.h"

namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

    QVector<QLineEdit*> vl;
    QVector<QLabel*> imgl ;
    QVector<QLabel*> namel ;
    QVector<QLabel*> pricel ;

    DataManager *dm;
    QVector <DetailedCartItem> dci;
    QVector <CartItem> upd;
    QVector< unsigned int>id,qu;
    QVector <QPixmap> img;
    QVector <QString> names;
    QVector <MoneyAmount> prices;
    unsigned int unavailItem , index;

public:
    explicit Cart(DataManager *dataManager, QWidget *parent = nullptr);
    ~Cart();

private slots:
    void on_pushButton_clicked();
    void on_Checkout_clicked();

    void on_b_clicked();

public slots:
    void checkout_slot(CheckoutResult result);
    void getCart_slot (QVector <DetailedCartItem> result);


private:
    Ui::Cart *ui;
};

#endif // CART_H
