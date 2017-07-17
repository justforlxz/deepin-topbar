/****************************************************************************
** Meta object code from reading C++ file 'pluginsitemcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controller/pluginsitemcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pluginsitemcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PluginsItemController_t {
    QByteArrayData data[8];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginsItemController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginsItemController_t qt_meta_stringdata_PluginsItemController = {
    {
QT_MOC_LITERAL(0, 0, 21), // "PluginsItemController"
QT_MOC_LITERAL(1, 22, 12), // "itemInserted"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 5), // "Item*"
QT_MOC_LITERAL(5, 48, 4), // "item"
QT_MOC_LITERAL(6, 53, 11), // "itemRemoved"
QT_MOC_LITERAL(7, 65, 8) // "itemSort"

    },
    "PluginsItemController\0itemInserted\0\0"
    "index\0Item*\0item\0itemRemoved\0itemSort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginsItemController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       6,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PluginsItemController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PluginsItemController *_t = static_cast<PluginsItemController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemInserted((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< Item*(*)>(_a[2]))); break;
        case 1: _t->itemRemoved((*reinterpret_cast< Item*(*)>(_a[1]))); break;
        case 2: _t->itemSort(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Item* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Item* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PluginsItemController::*_t)(const int , Item * ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginsItemController::itemInserted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PluginsItemController::*_t)(Item * ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginsItemController::itemRemoved)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PluginsItemController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PluginsItemController.data,
      qt_meta_data_PluginsItemController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PluginsItemController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginsItemController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PluginsItemController.stringdata0))
        return static_cast<void*>(const_cast< PluginsItemController*>(this));
    return QObject::qt_metacast(_clname);
}

int PluginsItemController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PluginsItemController::itemInserted(const int _t1, Item * _t2)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(const_cast< PluginsItemController *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PluginsItemController::itemRemoved(Item * _t1)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< PluginsItemController *>(this), &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
