/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *logButton;
    QPushButton *regButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *emailLog;
    QLineEdit *passLog;
    QLabel *label_5;
    QCheckBox *checkBox;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(900, 602);
        Login->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(207, 220, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 251, 151));
        label->setStyleSheet(QString::fromUtf8("font: 26pt \"Forte\";\n"
"\n"
"background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(420, 130, 91, 41));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        logButton = new QPushButton(Login);
        logButton->setObjectName(QString::fromUtf8("logButton"));
        logButton->setGeometry(QRect(610, 400, 121, 61));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        logButton->setFont(font1);
        logButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        regButton = new QPushButton(Login);
        regButton->setObjectName(QString::fromUtf8("regButton"));
        regButton->setGeometry(QRect(370, 490, 131, 61));
        regButton->setFont(font1);
        regButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gridLayoutWidget = new QWidget(Login);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(190, 180, 541, 151));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        emailLog = new QLineEdit(gridLayoutWidget);
        emailLog->setObjectName(QString::fromUtf8("emailLog"));
        emailLog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(emailLog, 0, 1, 1, 1);

        passLog = new QLineEdit(gridLayoutWidget);
        passLog->setObjectName(QString::fromUtf8("passLog"));
        passLog->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        passLog->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passLog, 1, 1, 1, 1);

        label_5 = new QLabel(Login);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(360, 450, 221, 31));
        QFont font3;
        font3.setPointSize(12);
        label_5->setFont(font3);
        label_5->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));
        checkBox = new QCheckBox(Login);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(610, 360, 141, 31));
        checkBox->setFont(font2);
        checkBox->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:2, fx:0.500038, fy:0.511, stop:0.370192 rgba(255, 255, 255, 0), stop:0.4 rgba(255, 162, 162, 80), stop:0.425 rgba(255, 132, 132, 156), stop:0.427885 rgba(255, 188, 188, 80), stop:0.44 rgba(252, 128, 128, 80), stop:1 rgba(255, 255, 255, 0));"));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Login", " TheMarket", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "Login", nullptr));
        logButton->setText(QCoreApplication::translate("Login", "Login", nullptr));
        regButton->setText(QCoreApplication::translate("Login", "Register", nullptr));
        label_4->setText(QCoreApplication::translate("Login", "Password", nullptr));
        label_3->setText(QCoreApplication::translate("Login", "E-mail", nullptr));
        label_5->setText(QCoreApplication::translate("Login", "Don't have an account ?", nullptr));
        checkBox->setText(QCoreApplication::translate("Login", "Remember me", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
