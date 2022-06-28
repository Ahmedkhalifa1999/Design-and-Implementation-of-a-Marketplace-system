#ifndef ITEM_H
#define ITEM_H

#include <QDialog>

namespace Ui {
class Item;
}

class Item : public QDialog
{
    Q_OBJECT

public:
    explicit Item(QWidget *parent = nullptr);
    ~Item();

private:
    Ui::Item *ui;
};

#endif // ITEM_H
