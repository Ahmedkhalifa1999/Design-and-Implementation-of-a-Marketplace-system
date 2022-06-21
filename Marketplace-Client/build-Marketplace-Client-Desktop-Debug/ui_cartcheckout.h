/********************************************************************************
** Form generated from reading UI file 'cartcheckout.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARTCHECKOUT_H
#define UI_CARTCHECKOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CartCheckout
{
public:

    void setupUi(QWidget *CartCheckout)
    {
        if (CartCheckout->objectName().isEmpty())
            CartCheckout->setObjectName(QString::fromUtf8("CartCheckout"));
        CartCheckout->resize(400, 300);

        retranslateUi(CartCheckout);

        QMetaObject::connectSlotsByName(CartCheckout);
    } // setupUi

    void retranslateUi(QWidget *CartCheckout)
    {
        CartCheckout->setWindowTitle(QCoreApplication::translate("CartCheckout", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CartCheckout: public Ui_CartCheckout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARTCHECKOUT_H
