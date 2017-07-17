/****************************************************************************
** Meta object code from reading C++ file 'itempopupwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "utils/itempopupwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'itempopupwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ItemPopupWindow_t {
    QByteArrayData data[9];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ItemPopupWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ItemPopupWindow_t qt_meta_stringdata_ItemPopupWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ItemPopupWindow"
QT_MOC_LITERAL(1, 16, 4), // "show"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "pos"
QT_MOC_LITERAL(4, 26, 1), // "x"
QT_MOC_LITERAL(5, 28, 1), // "y"
QT_MOC_LITERAL(6, 30, 16), // "compositeChanged"
QT_MOC_LITERAL(7, 47, 13), // "containsPoint"
QT_MOC_LITERAL(8, 61, 5) // "point"

    },
    "ItemPopupWindow\0show\0\0pos\0x\0y\0"
    "compositeChanged\0containsPoint\0point"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ItemPopupWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       1,    2,   37,    2, 0x0a /* Public */,
       6,    0,   42,    2, 0x08 /* Private */,
       7,    1,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QPoint,    8,

       0        // eod
};

void ItemPopupWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ItemPopupWindow *_t = static_cast<ItemPopupWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->show((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->show((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 2: _t->compositeChanged(); break;
        case 3: { bool _r = _t->containsPoint((*reinterpret_cast< const QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject ItemPopupWindow::staticMetaObject = {
    { &Dtk::Widget::DArrowRectangle::staticMetaObject, qt_meta_stringdata_ItemPopupWindow.data,
      qt_meta_data_ItemPopupWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ItemPopupWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ItemPopupWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ItemPopupWindow.stringdata0))
        return static_cast<void*>(const_cast< ItemPopupWindow*>(this));
    return Dtk::Widget::DArrowRectangle::qt_metacast(_clname);
}

int ItemPopupWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Dtk::Widget::DArrowRectangle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
