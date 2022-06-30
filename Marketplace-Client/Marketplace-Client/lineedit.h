#ifndef LINEEDIT_H
#define LINEEDIT_H

#include<QLineEdit>
#include <QWidget>

class LineEdit : public QLineEdit
{
public:
    LineEdit();
    unsigned int id;
};

#endif // LINEEDIT_H
