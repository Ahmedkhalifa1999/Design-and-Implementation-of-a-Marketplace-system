/********************************************************************************
** Form generated from reading UI file 'itemview.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMVIEW_H
#define UI_ITEMVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemView
{
public:

    void setupUi(QWidget *ItemView)
    {
        if (ItemView->objectName().isEmpty())
            ItemView->setObjectName(QString::fromUtf8("ItemView"));
        ItemView->resize(400, 300);

        retranslateUi(ItemView);

        QMetaObject::connectSlotsByName(ItemView);
    } // setupUi

    void retranslateUi(QWidget *ItemView)
    {
        ItemView->setWindowTitle(QCoreApplication::translate("ItemView", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ItemView: public Ui_ItemView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMVIEW_H
