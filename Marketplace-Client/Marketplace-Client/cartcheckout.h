#ifndef CARTCHECKOUT_H
#define CARTCHECKOUT_H

#include <QWidget>

namespace Ui {
class CartCheckout;
}

class CartCheckout : public QWidget
{
    Q_OBJECT

public:
    explicit CartCheckout(QWidget *parent = nullptr);
    ~CartCheckout();

private:
    Ui::CartCheckout *ui;
};

#endif // CARTCHECKOUT_H
