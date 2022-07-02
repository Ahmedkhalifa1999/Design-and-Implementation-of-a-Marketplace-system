/********************************************************************************
** Form generated from reading UI file 'account.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNT_H
#define UI_ACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Account
{
public:
    QLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_14;
    QLineEdit *email;
    QPushButton *save;
    QLineEdit *phone;
    QLabel *label_12;
    QLineEdit *name;
    QLineEdit *address;
    QLabel *label_5;
    QLabel *label_15;
    QLabel *label_9;
    QLabel *balance;
    QLabel *label_7;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QLabel *label_4;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_2;
    QLineEdit *poundLine;
    QLabel *label_8;
    QLineEdit *piasterLine;
    QLabel *label_6;
    QPushButton *deposit;
    QLabel *label_10;
    QLabel *label_11;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout_4;

    void setupUi(QDialog *Account)
    {
        if (Account->objectName().isEmpty())
            Account->setObjectName(QString::fromUtf8("Account"));
        Account->resize(1157, 619);
        Account->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(207, 220, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        label = new QLabel(Account);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 250, 150));
        label->setStyleSheet(QString::fromUtf8("font: 26pt \"Forte\";\n"
"\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        label_2 = new QLabel(Account);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 120, 171, 20));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("\n"
"\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        layoutWidget = new QWidget(Account);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 160, 521, 437));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label_14->setFont(font1);
        label_14->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_14, 8, 0, 1, 1);

        email = new QLineEdit(layoutWidget);
        email->setObjectName(QString::fromUtf8("email"));
        email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(email, 3, 0, 1, 2);

        save = new QPushButton(layoutWidget);
        save->setObjectName(QString::fromUtf8("save"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        save->setFont(font2);
        save->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(save, 10, 1, 1, 1);

        phone = new QLineEdit(layoutWidget);
        phone->setObjectName(QString::fromUtf8("phone"));
        phone->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(phone, 7, 0, 1, 2);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);
        label_12->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_12, 6, 0, 1, 1);

        name = new QLineEdit(layoutWidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(name, 1, 0, 1, 2);

        address = new QLineEdit(layoutWidget);
        address->setObjectName(QString::fromUtf8("address"));
        address->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(address, 5, 0, 1, 2);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font1);
        label_15->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_15, 9, 1, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        balance = new QLabel(layoutWidget);
        balance->setObjectName(QString::fromUtf8("balance"));
        balance->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(balance, 9, 0, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        layoutWidget1 = new QWidget(Account);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(740, 20, 401, 91));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font2);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(207, 220, 255, 255), stop:1 rgba(255, 255, 255, 255));"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(207, 220, 255, 255), stop:1 rgba(255, 255, 255, 255));"));

        horizontalLayout->addWidget(pushButton);

        label_4 = new QLabel(Account);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(550, 130, 78, 27));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        gridLayoutWidget = new QWidget(Account);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(550, 170, 311, 101));
        gridLayout_2 = new QGridLayout(gridLayoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        poundLine = new QLineEdit(gridLayoutWidget);
        poundLine->setObjectName(QString::fromUtf8("poundLine"));
        poundLine->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(poundLine, 0, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font3;
        font3.setBold(true);
        label_8->setFont(font3);
        label_8->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        piasterLine = new QLineEdit(gridLayoutWidget);
        piasterLine->setObjectName(QString::fromUtf8("piasterLine"));
        piasterLine->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(piasterLine, 1, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font3);
        label_6->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        deposit = new QPushButton(gridLayoutWidget);
        deposit->setObjectName(QString::fromUtf8("deposit"));
        deposit->setFont(font2);
        deposit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout_2->addWidget(deposit, 2, 1, 1, 1);

        label_10 = new QLabel(Account);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(550, 280, 141, 31));
        label_10->setFont(font1);
        label_10->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        label_11 = new QLabel(Account);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(860, 280, 271, 31));
        label_11->setFont(font1);
        label_11->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        scrollArea = new QScrollArea(Account);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(550, 330, 281, 261));
        scrollArea->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 279, 259));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));

        horizontalLayout_2->addLayout(gridLayout_3);

        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollArea_2 = new QScrollArea(Account);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(860, 330, 281, 261));
        scrollArea_2->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 279, 259));
        horizontalLayout_3 = new QHBoxLayout(scrollAreaWidgetContents_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));

        horizontalLayout_3->addLayout(gridLayout_4);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        retranslateUi(Account);

        QMetaObject::connectSlotsByName(Account);
    } // setupUi

    void retranslateUi(QDialog *Account)
    {
        Account->setWindowTitle(QCoreApplication::translate("Account", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Account", " TheMarket", nullptr));
        label_2->setText(QCoreApplication::translate("Account", "Account Details", nullptr));
        label_14->setText(QCoreApplication::translate("Account", "Balance", nullptr));
        save->setText(QCoreApplication::translate("Account", "Update", nullptr));
        label_12->setText(QCoreApplication::translate("Account", "Phone", nullptr));
        name->setText(QString());
        label_5->setText(QCoreApplication::translate("Account", "Name", nullptr));
        label_15->setText(QCoreApplication::translate("Account", "EGP", nullptr));
        label_9->setText(QCoreApplication::translate("Account", "Address", nullptr));
        balance->setText(QString());
        label_7->setText(QCoreApplication::translate("Account", "Email", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Account", "Cart", nullptr));
        pushButton->setText(QCoreApplication::translate("Account", "Home", nullptr));
        label_4->setText(QCoreApplication::translate("Account", "Deposit:", nullptr));
        label_8->setText(QCoreApplication::translate("Account", "Pounds:", nullptr));
        label_6->setText(QCoreApplication::translate("Account", "Piasters:", nullptr));
        deposit->setText(QCoreApplication::translate("Account", "Deposit", nullptr));
        label_10->setText(QCoreApplication::translate("Account", "Order history:", nullptr));
        label_11->setText(QCoreApplication::translate("Account", "Order details of  an order:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Account: public Ui_Account {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNT_H
