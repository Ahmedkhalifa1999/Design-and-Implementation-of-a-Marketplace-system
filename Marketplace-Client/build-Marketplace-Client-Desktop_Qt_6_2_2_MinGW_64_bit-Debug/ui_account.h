/********************************************************************************
** Form generated from reading UI file 'account.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNT_H
#define UI_ACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Account
{
public:
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *Account)
    {
        if (Account->objectName().isEmpty())
            Account->setObjectName(QString::fromUtf8("Account"));
        Account->resize(900, 600);
        Account->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(207, 220, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        label = new QLabel(Account);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 250, 150));
        label->setStyleSheet(QString::fromUtf8("font: 26pt \"Forte\";\n"
"\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        label_2 = new QLabel(Account);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(360, 110, 161, 20));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("\n"
"\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        retranslateUi(Account);

        QMetaObject::connectSlotsByName(Account);
    } // setupUi

    void retranslateUi(QDialog *Account)
    {
        Account->setWindowTitle(QCoreApplication::translate("Account", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Account", "TheMarket", nullptr));
        label_2->setText(QCoreApplication::translate("Account", "Account Details", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Account: public Ui_Account {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNT_H
