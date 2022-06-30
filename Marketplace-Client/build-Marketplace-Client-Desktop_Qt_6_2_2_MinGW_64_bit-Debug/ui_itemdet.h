/********************************************************************************
** Form generated from reading UI file 'itemdet.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMDET_H
#define UI_ITEMDET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Itemdet
{
public:
    QLabel *label;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *shopButton;
    QPushButton *addCartButton;

    void setupUi(QDialog *Itemdet)
    {
        if (Itemdet->objectName().isEmpty())
            Itemdet->setObjectName(QString::fromUtf8("Itemdet"));
        Itemdet->resize(900, 600);
        QFont font;
        font.setPointSize(14);
        Itemdet->setFont(font);
        Itemdet->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(207, 220, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        label = new QLabel(Itemdet);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 250, 150));
        label->setStyleSheet(QString::fromUtf8("font: 26pt \"Forte\";\n"
"\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        label_2 = new QLabel(Itemdet);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(380, 80, 151, 41));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("\n"
"\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        scrollArea = new QScrollArea(Itemdet);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(70, 140, 781, 351));
        scrollArea->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 779, 349));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        horizontalLayout->addLayout(gridLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);
        shopButton = new QPushButton(Itemdet);
        shopButton->setObjectName(QString::fromUtf8("shopButton"));
        shopButton->setGeometry(QRect(80, 510, 171, 60));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        shopButton->setFont(font2);
        shopButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        addCartButton = new QPushButton(Itemdet);
        addCartButton->setObjectName(QString::fromUtf8("addCartButton"));
        addCartButton->setGeometry(QRect(680, 510, 171, 60));
        addCartButton->setFont(font2);
        addCartButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(Itemdet);

        QMetaObject::connectSlotsByName(Itemdet);
    } // setupUi

    void retranslateUi(QDialog *Itemdet)
    {
        Itemdet->setWindowTitle(QCoreApplication::translate("Itemdet", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Itemdet", " TheMarket", nullptr));
        label_2->setText(QCoreApplication::translate("Itemdet", "Item Details", nullptr));
        shopButton->setText(QCoreApplication::translate("Itemdet", "Back To Shop", nullptr));
        addCartButton->setText(QCoreApplication::translate("Itemdet", "Add To Cart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Itemdet: public Ui_Itemdet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMDET_H
