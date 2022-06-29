#ifndef ITEMDET_H
#define ITEMDET_H

#include <QDialog>

namespace Ui {
class Itemdet;
}

class Itemdet : public QDialog
{
    Q_OBJECT

public:
    explicit Itemdet(QWidget *parent = nullptr);
    ~Itemdet();

private:
    Ui::Itemdet *ui;
};

#endif // ITEMDET_H
