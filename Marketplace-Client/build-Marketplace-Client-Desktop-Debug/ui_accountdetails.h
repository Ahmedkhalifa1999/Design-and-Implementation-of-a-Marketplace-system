/********************************************************************************
** Form generated from reading UI file 'accountdetails.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTDETAILS_H
#define UI_ACCOUNTDETAILS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountDetails
{
public:

    void setupUi(QWidget *AccountDetails)
    {
        if (AccountDetails->objectName().isEmpty())
            AccountDetails->setObjectName(QString::fromUtf8("AccountDetails"));
        AccountDetails->resize(400, 300);

        retranslateUi(AccountDetails);

        QMetaObject::connectSlotsByName(AccountDetails);
    } // setupUi

    void retranslateUi(QWidget *AccountDetails)
    {
        AccountDetails->setWindowTitle(QCoreApplication::translate("AccountDetails", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountDetails: public Ui_AccountDetails {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTDETAILS_H
