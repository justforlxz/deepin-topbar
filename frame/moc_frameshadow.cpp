/****************************************************************************
** Meta object code from reading C++ file 'frameshadow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "frameshadow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frameshadow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FrameShadow_t {
    QByteArrayData data[3];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FrameShadow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FrameShadow_t qt_meta_stringdata_FrameShadow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FrameShadow"
QT_MOC_LITERAL(1, 12, 13), // "screenChanged"
QT_MOC_LITERAL(2, 26, 0) // ""

    },
    "FrameShadow\0screenChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrameShadow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void FrameShadow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FrameShadow *_t = static_cast<FrameShadow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->screenChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FrameShadow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrameShadow.data,
      qt_meta_data_FrameShadow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FrameShadow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameShadow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FrameShadow.stringdata0))
        return static_cast<void*>(const_cast< FrameShadow*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrameShadow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
