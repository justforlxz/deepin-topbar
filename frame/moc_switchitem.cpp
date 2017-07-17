/****************************************************************************
** Meta object code from reading C++ file 'switchitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgets/switchitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'switchitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_topbar__widgets__SwitchItem_t {
    QByteArrayData data[9];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_topbar__widgets__SwitchItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_topbar__widgets__SwitchItem_t qt_meta_stringdata_topbar__widgets__SwitchItem = {
    {
QT_MOC_LITERAL(0, 0, 27), // "topbar::widgets::SwitchItem"
QT_MOC_LITERAL(1, 28, 7), // "clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "state"
QT_MOC_LITERAL(4, 43, 7), // "setText"
QT_MOC_LITERAL(5, 51, 4), // "text"
QT_MOC_LITERAL(6, 56, 8), // "setCheck"
QT_MOC_LITERAL(7, 65, 8), // "setValue"
QT_MOC_LITERAL(8, 74, 5) // "value"

    },
    "topbar::widgets::SwitchItem\0clicked\0"
    "\0state\0setText\0text\0setCheck\0setValue\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_topbar__widgets__SwitchItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void topbar::widgets::SwitchItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SwitchItem *_t = static_cast<SwitchItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setCheck((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 3: _t->setValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SwitchItem::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SwitchItem::clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject topbar::widgets::SwitchItem::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_topbar__widgets__SwitchItem.data,
      qt_meta_data_topbar__widgets__SwitchItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *topbar::widgets::SwitchItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *topbar::widgets::SwitchItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_topbar__widgets__SwitchItem.stringdata0))
        return static_cast<void*>(const_cast< SwitchItem*>(this));
    return QWidget::qt_metacast(_clname);
}

int topbar::widgets::SwitchItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void topbar::widgets::SwitchItem::clicked(const bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
