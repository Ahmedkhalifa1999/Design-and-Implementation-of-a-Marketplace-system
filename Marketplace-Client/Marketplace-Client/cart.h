#ifndef CART_H
#define CART_H

#include <QDialog>
#include"datamanager.h"
namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr);
    ~Cart();

private slots:
    void on_pushButton_clicked();
    void on_Checkout_clicked();
    void checkout_slot(bool result, std::vector<CheckoutResult> detailedResult);


private:
    Ui::Cart *ui;
};

#endif // CART_H
