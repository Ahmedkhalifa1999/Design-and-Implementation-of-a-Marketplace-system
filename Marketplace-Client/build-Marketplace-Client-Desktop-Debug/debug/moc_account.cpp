/****************************************************************************
** Meta object code from reading C++ file 'account.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Marketplace-Client/account.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'account.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Account_t {
    const uint offsetsAndSize[44];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Account_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Account_t qt_meta_stringdata_Account = {
    {
QT_MOC_LITERAL(0, 7), // "Account"
QT_MOC_LITERAL(8, 15), // "on_butt_clicked"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 15), // "on_save_clicked"
QT_MOC_LITERAL(41, 26), // "on_address_editingFinished"
QT_MOC_LITERAL(68, 24), // "on_phone_editingFinished"
QT_MOC_LITERAL(93, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(115, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(139, 18), // "on_deposit_clicked"
QT_MOC_LITERAL(158, 23), // "on_name_editingFinished"
QT_MOC_LITERAL(182, 13), // "walletDeposit"
QT_MOC_LITERAL(196, 11), // "MoneyAmount"
QT_MOC_LITERAL(208, 6), // "amount"
QT_MOC_LITERAL(215, 22), // "getAccountDetails_slot"
QT_MOC_LITERAL(238, 14), // "AccountDetails"
QT_MOC_LITERAL(253, 6), // "result"
QT_MOC_LITERAL(260, 25), // "updateAccountDetails_slot"
QT_MOC_LITERAL(286, 18), // "walletDeposit_slot"
QT_MOC_LITERAL(305, 20), // "getOrderHistory_slot"
QT_MOC_LITERAL(326, 19), // "QList<OrderSummary>"
QT_MOC_LITERAL(346, 20), // "getOrderDetails_slot"
QT_MOC_LITERAL(367, 13) // "DetailedOrder"

    },
    "Account\0on_butt_clicked\0\0on_save_clicked\0"
    "on_address_editingFinished\0"
    "on_phone_editingFinished\0on_pushButton_clicked\0"
    "on_pushButton_2_clicked\0on_deposit_clicked\0"
    "on_name_editingFinished\0walletDeposit\0"
    "MoneyAmount\0amount\0getAccountDetails_slot\0"
    "AccountDetails\0result\0updateAccountDetails_slot\0"
    "walletDeposit_slot\0getOrderHistory_slot\0"
    "QList<OrderSummary>\0getOrderDetails_slot\0"
    "DetailedOrder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Account[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    1 /* Private */,
       3,    0,   99,    2, 0x08,    2 /* Private */,
       4,    0,  100,    2, 0x08,    3 /* Private */,
       5,    0,  101,    2, 0x08,    4 /* Private */,
       6,    0,  102,    2, 0x08,    5 /* Private */,
       7,    0,  103,    2, 0x08,    6 /* Private */,
       8,    0,  104,    2, 0x08,    7 /* Private */,
       9,    0,  105,    2, 0x08,    8 /* Private */,
      10,    1,  106,    2, 0x08,    9 /* Private */,
      13,    1,  109,    2, 0x0a,   11 /* Public */,
      16,    1,  112,    2, 0x0a,   13 /* Public */,
      17,    1,  115,    2, 0x0a,   15 /* Public */,
      18,    1,  118,    2, 0x0a,   17 /* Public */,
      20,    1,  121,    2, 0x0a,   19 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, 0x80000000 | 19,   15,
    QMetaType::Void, 0x80000000 | 21,   15,

       0        // eod
};

void Account::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Account *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_butt_clicked(); break;
        case 1: _t->on_save_clicked(); break;
        case 2: _t->on_address_editingFinished(); break;
        case 3: _t->on_phone_editingFinished(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        case 6: _t->on_deposit_clicked(); break;
        case 7: _t->on_name_editingFinished(); break;
        case 8: _t->walletDeposit((*reinterpret_cast< std::add_pointer_t<MoneyAmount>>(_a[1]))); break;
        case 9: _t->getAccountDetails_slot((*reinterpret_cast< std::add_pointer_t<AccountDetails>>(_a[1]))); break;
        case 10: _t->updateAccountDetails_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->walletDeposit_slot((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->getOrderHistory_slot((*reinterpret_cast< std::add_pointer_t<QList<OrderSummary>>>(_a[1]))); break;
        case 13: _t->getOrderDetails_slot((*reinterpret_cast< std::add_pointer_t<DetailedOrder>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Account::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Account.offsetsAndSize,
    qt_meta_data_Account,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Account_t
, QtPrivate::TypeAndForceComplete<Account, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<MoneyAmount, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<AccountDetails, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<OrderSummary>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<DetailedOrder, std::false_type>


>,
    nullptr
} };


const QMetaObject *Account::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Account::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Account.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Account::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
