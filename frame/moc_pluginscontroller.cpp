/****************************************************************************
** Meta object code from reading C++ file 'pluginscontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controller/pluginscontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pluginscontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PluginsController_t {
    QByteArrayData data[11];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginsController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginsController_t qt_meta_stringdata_PluginsController = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PluginsController"
QT_MOC_LITERAL(1, 18, 18), // "pluginItemInserted"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 12), // "PluginsItem*"
QT_MOC_LITERAL(4, 51, 10), // "pluginItem"
QT_MOC_LITERAL(5, 62, 17), // "pluginItemRemoved"
QT_MOC_LITERAL(6, 80, 17), // "pluginItemUpdated"
QT_MOC_LITERAL(7, 98, 18), // "pluginItemFinished"
QT_MOC_LITERAL(8, 117, 11), // "startLoader"
QT_MOC_LITERAL(9, 129, 10), // "loadPlugin"
QT_MOC_LITERAL(10, 140, 10) // "pluginFile"

    },
    "PluginsController\0pluginItemInserted\0"
    "\0PluginsItem*\0pluginItem\0pluginItemRemoved\0"
    "pluginItemUpdated\0pluginItemFinished\0"
    "startLoader\0loadPlugin\0pluginFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginsController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       7,    0,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   54,    2, 0x08 /* Private */,
       9,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void PluginsController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PluginsController *_t = static_cast<PluginsController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pluginItemInserted((*reinterpret_cast< PluginsItem*(*)>(_a[1]))); break;
        case 1: _t->pluginItemRemoved((*reinterpret_cast< PluginsItem*(*)>(_a[1]))); break;
        case 2: _t->pluginItemUpdated((*reinterpret_cast< PluginsItem*(*)>(_a[1]))); break;
        case 3: _t->pluginItemFinished(); break;
        case 4: _t->startLoader(); break;
        case 5: _t->loadPlugin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PluginsItem* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PluginsItem* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PluginsItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PluginsController::*_t)(PluginsItem * ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginsController::pluginItemInserted)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PluginsController::*_t)(PluginsItem * ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginsController::pluginItemRemoved)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PluginsController::*_t)(PluginsItem * ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginsController::pluginItemUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PluginsController::*_t)() const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PluginsController::pluginItemFinished)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject PluginsController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PluginsController.data,
      qt_meta_data_PluginsController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PluginsController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginsController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PluginsController.stringdata0))
        return static_cast<void*>(const_cast< PluginsController*>(this));
    if (!strcmp(_clname, "PluginProxyInterface"))
        return static_cast< PluginProxyInterface*>(const_cast< PluginsController*>(this));
    return QObject::qt_metacast(_clname);
}

int PluginsController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PluginsController::pluginItemInserted(PluginsItem * _t1)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< PluginsController *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PluginsController::pluginItemRemoved(PluginsItem * _t1)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< PluginsController *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PluginsController::pluginItemUpdated(PluginsItem * _t1)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< PluginsController *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PluginsController::pluginItemFinished()const
{
    QMetaObject::activate(const_cast< PluginsController *>(this), &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
