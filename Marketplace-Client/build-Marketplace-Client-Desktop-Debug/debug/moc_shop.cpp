/****************************************************************************
** Meta object code from reading C++ file 'shop.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Marketplace-Client/shop.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shop.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Shop_t {
    const uint offsetsAndSize[20];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Shop_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Shop_t qt_meta_stringdata_Shop = {
    {
QT_MOC_LITERAL(0, 4), // "Shop"
QT_MOC_LITERAL(5, 12), // "on_b_clicked"
QT_MOC_LITERAL(18, 0), // ""
QT_MOC_LITERAL(19, 21), // "on_cartButton_clicked"
QT_MOC_LITERAL(41, 24), // "on_accountButton_clicked"
QT_MOC_LITERAL(66, 23), // "on_searchButton_clicked"
QT_MOC_LITERAL(90, 18), // "getCategories_slot"
QT_MOC_LITERAL(109, 6), // "result"
QT_MOC_LITERAL(116, 16), // "getItemList_slot"
QT_MOC_LITERAL(133, 11) // "QList<Item>"

    },
    "Shop\0on_b_clicked\0\0on_cartButton_clicked\0"
    "on_accountButton_clicked\0"
    "on_searchButton_clicked\0getCategories_slot\0"
    "result\0getItemList_slot\0QList<Item>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Shop[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    1,   54,    2, 0x0a,    5 /* Public */,
       8,    1,   57,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    7,
    QMetaType::Void, 0x80000000 | 9,    7,

       0        // eod
};

void Shop::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Shop *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_b_clicked(); break;
        case 1: _t->on_cartButton_clicked(); break;
        case 2: _t->on_accountButton_clicked(); break;
        case 3: _t->on_searchButton_clicked(); break;
        case 4: _t->getCategories_slot((*reinterpret_cast< std::add_pointer_t<QList<QString>>>(_a[1]))); break;
        case 5: _t->getItemList_slot((*reinterpret_cast< std::add_pointer_t<QList<Item>>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Shop::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Shop.offsetsAndSize,
    qt_meta_data_Shop,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Shop_t
, QtPrivate::TypeAndForceComplete<Shop, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<QString>, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<Item>, std::false_type>


>,
    nullptr
} };


const QMetaObject *Shop::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Shop::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Shop.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Shop::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
