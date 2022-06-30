/****************************************************************************
** Meta object code from reading C++ file 'datamanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Marketplace-Client/datamanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datamanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataManager_t {
    const uint offsetsAndSize[44];
    char stringdata0[380];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DataManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DataManager_t qt_meta_stringdata_DataManager = {
    {
QT_MOC_LITERAL(0, 11), // "DataManager"
QT_MOC_LITERAL(12, 13), // "signUp_signal"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 6), // "result"
QT_MOC_LITERAL(34, 13), // "signIn_signal"
QT_MOC_LITERAL(48, 15), // "checkout_signal"
QT_MOC_LITERAL(64, 14), // "CheckoutResult"
QT_MOC_LITERAL(79, 14), // "detailedResult"
QT_MOC_LITERAL(94, 24), // "getAccountDetails_signal"
QT_MOC_LITERAL(119, 14), // "AccountDetails"
QT_MOC_LITERAL(134, 27), // "updateAccountDetails_signal"
QT_MOC_LITERAL(162, 22), // "getOrderHistory_signal"
QT_MOC_LITERAL(185, 25), // "std::vector<OrderSummary>"
QT_MOC_LITERAL(211, 22), // "getOrderDetails_signal"
QT_MOC_LITERAL(234, 13), // "DetailedOrder"
QT_MOC_LITERAL(248, 20), // "walletDeposit_signal"
QT_MOC_LITERAL(269, 18), // "getItemList_signal"
QT_MOC_LITERAL(288, 17), // "std::vector<Item>"
QT_MOC_LITERAL(306, 18), // "getItemData_signal"
QT_MOC_LITERAL(325, 12), // "DetailedItem"
QT_MOC_LITERAL(338, 20), // "getCategories_signal"
QT_MOC_LITERAL(359, 20) // "std::vector<QString>"

    },
    "DataManager\0signUp_signal\0\0result\0"
    "signIn_signal\0checkout_signal\0"
    "CheckoutResult\0detailedResult\0"
    "getAccountDetails_signal\0AccountDetails\0"
    "updateAccountDetails_signal\0"
    "getOrderHistory_signal\0std::vector<OrderSummary>\0"
    "getOrderDetails_signal\0DetailedOrder\0"
    "walletDeposit_signal\0getItemList_signal\0"
    "std::vector<Item>\0getItemData_signal\0"
    "DetailedItem\0getCategories_signal\0"
    "std::vector<QString>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,
       4,    1,   83,    2, 0x06,    3 /* Public */,
       5,    1,   86,    2, 0x06,    5 /* Public */,
       8,    1,   89,    2, 0x06,    7 /* Public */,
      10,    1,   92,    2, 0x06,    9 /* Public */,
      11,    1,   95,    2, 0x06,   11 /* Public */,
      13,    1,   98,    2, 0x06,   13 /* Public */,
      15,    1,  101,    2, 0x06,   15 /* Public */,
      16,    1,  104,    2, 0x06,   17 /* Public */,
      18,    1,  107,    2, 0x06,   19 /* Public */,
      20,    1,  110,    2, 0x06,   21 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 12,    3,
    QMetaType::Void, 0x80000000 | 14,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 17,    3,
    QMetaType::Void, 0x80000000 | 19,    3,
    QMetaType::Void, 0x80000000 | 21,    3,

       0        // eod
};

void DataManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signUp_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->signIn_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->checkout_signal((*reinterpret_cast< CheckoutResult(*)>(_a[1]))); break;
        case 3: _t->getAccountDetails_signal((*reinterpret_cast< AccountDetails(*)>(_a[1]))); break;
        case 4: _t->updateAccountDetails_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->getOrderHistory_signal((*reinterpret_cast< std::vector<OrderSummary>(*)>(_a[1]))); break;
        case 6: _t->getOrderDetails_signal((*reinterpret_cast< DetailedOrder(*)>(_a[1]))); break;
        case 7: _t->walletDeposit_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->getItemList_signal((*reinterpret_cast< std::vector<Item>(*)>(_a[1]))); break;
        case 9: _t->getItemData_signal((*reinterpret_cast< DetailedItem(*)>(_a[1]))); break;
        case 10: _t->getCategories_signal((*reinterpret_cast< std::vector<QString>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::signUp_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::signIn_signal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(CheckoutResult );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::checkout_signal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(AccountDetails );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::getAccountDetails_signal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::updateAccountDetails_signal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(std::vector<OrderSummary> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::getOrderHistory_signal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(DetailedOrder );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::getOrderDetails_signal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::walletDeposit_signal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(std::vector<Item> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::getItemList_signal)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(DetailedItem );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::getItemData_signal)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (DataManager::*)(std::vector<QString> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataManager::getCategories_signal)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject DataManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DataManager.offsetsAndSize,
    qt_meta_data_DataManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DataManager_t
, QtPrivate::TypeAndForceComplete<DataManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<CheckoutResult, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<AccountDetails, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<OrderSummary>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<DetailedOrder, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<Item>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<DetailedItem, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::vector<QString>, std::false_type>



>,
    nullptr
} };


const QMetaObject *DataManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DataManager::signUp_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataManager::signIn_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataManager::checkout_signal(CheckoutResult _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataManager::getAccountDetails_signal(AccountDetails _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DataManager::updateAccountDetails_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DataManager::getOrderHistory_signal(std::vector<OrderSummary> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DataManager::getOrderDetails_signal(DetailedOrder _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DataManager::walletDeposit_signal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DataManager::getItemList_signal(std::vector<Item> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DataManager::getItemData_signal(DetailedItem _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void DataManager::getCategories_signal(std::vector<QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
