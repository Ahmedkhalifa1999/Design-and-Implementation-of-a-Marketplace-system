/********************************************************************************
** Form generated from reading UI file 'signinsignup.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNINSIGNUP_H
#define UI_SIGNINSIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignInSignUp
{
public:

    void setupUi(QWidget *SignInSignUp)
    {
        if (SignInSignUp->objectName().isEmpty())
            SignInSignUp->setObjectName(QString::fromUtf8("SignInSignUp"));
        SignInSignUp->resize(400, 300);

        retranslateUi(SignInSignUp);

        QMetaObject::connectSlotsByName(SignInSignUp);
    } // setupUi

    void retranslateUi(QWidget *SignInSignUp)
    {
        SignInSignUp->setWindowTitle(QCoreApplication::translate("SignInSignUp", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignInSignUp: public Ui_SignInSignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNINSIGNUP_H
