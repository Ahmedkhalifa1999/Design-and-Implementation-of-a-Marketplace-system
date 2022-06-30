/********************************************************************************
** Form generated from reading UI file 'cart.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CART_H
#define UI_CART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cart
{
public:
    QLabel *label;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *Checkout;

    void setupUi(QDialog *Cart)
    {
        if (Cart->objectName().isEmpty())
            Cart->setObjectName(QString::fromUtf8("Cart"));
        Cart->resize(900, 600);
        QFont font;
        font.setPointSize(14);
        Cart->setFont(font);
        Cart->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(207, 220, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        label = new QLabel(Cart);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 250, 150));
        label->setStyleSheet(QString::fromUtf8("font: 26pt \"Forte\";\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        label_2 = new QLabel(Cart);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 110, 111, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        scrollArea = new QScrollArea(Cart);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(20, 150, 671, 431));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 669, 429));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        horizontalLayout->addLayout(gridLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);
        layoutWidget = new QWidget(Cart);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(711, 420, 171, 151));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(pushButton);

        Checkout = new QPushButton(layoutWidget);
        Checkout->setObjectName(QString::fromUtf8("Checkout"));
        Checkout->setFont(font2);
        Checkout->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(Checkout);


        retranslateUi(Cart);

        QMetaObject::connectSlotsByName(Cart);
    } // setupUi

    void retranslateUi(QDialog *Cart)
    {
        Cart->setWindowTitle(QCoreApplication::translate("Cart", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Cart", " TheMarket", nullptr));
        label_2->setText(QCoreApplication::translate("Cart", "Cart", nullptr));
        pushButton->setText(QCoreApplication::translate("Cart", "Update Cart", nullptr));
        Checkout->setText(QCoreApplication::translate("Cart", "Checkout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cart: public Ui_Cart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CART_H
