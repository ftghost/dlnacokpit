/****************************************************************************
** Meta object code from reading C++ file 'GetDeviceData.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GetDeviceData.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GetDeviceData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GetDeviceData_t {
    QByteArrayData data[6];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GetDeviceData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GetDeviceData_t qt_meta_stringdata_GetDeviceData = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GetDeviceData"
QT_MOC_LITERAL(1, 14, 7), // "termine"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "index"
QT_MOC_LITERAL(4, 29, 4), // "isOk"
QT_MOC_LITERAL(5, 34, 8) // "IsServer"

    },
    "GetDeviceData\0termine\0\0index\0isOk\0"
    "IsServer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetDeviceData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,

       0        // eod
};

void GetDeviceData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GetDeviceData *_t = static_cast<GetDeviceData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->termine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GetDeviceData::*_t)(int , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetDeviceData::termine)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject GetDeviceData::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_GetDeviceData.data,
      qt_meta_data_GetDeviceData,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GetDeviceData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GetDeviceData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GetDeviceData.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int GetDeviceData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GetDeviceData::termine(int _t1, bool _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
