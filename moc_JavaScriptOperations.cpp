/****************************************************************************
** Meta object code from reading C++ file 'JavaScriptOperations.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "JavaScriptOperations.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'JavaScriptOperations.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_JavaScriptOperations_t {
    QByteArrayData data[5];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JavaScriptOperations_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JavaScriptOperations_t qt_meta_stringdata_JavaScriptOperations = {
    {
QT_MOC_LITERAL(0, 0, 20), // "JavaScriptOperations"
QT_MOC_LITERAL(1, 21, 6), // "submit"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "display"
QT_MOC_LITERAL(4, 37, 3) // "val"

    },
    "JavaScriptOperations\0submit\0\0display\0"
    "val"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JavaScriptOperations[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,    4,

       0        // eod
};

void JavaScriptOperations::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JavaScriptOperations *_t = static_cast<JavaScriptOperations *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->submit(); break;
        case 1: { QString _r = _t->display((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject JavaScriptOperations::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JavaScriptOperations.data,
      qt_meta_data_JavaScriptOperations,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *JavaScriptOperations::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JavaScriptOperations::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_JavaScriptOperations.stringdata0))
        return static_cast<void*>(const_cast< JavaScriptOperations*>(this));
    return QObject::qt_metacast(_clname);
}

int JavaScriptOperations::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
