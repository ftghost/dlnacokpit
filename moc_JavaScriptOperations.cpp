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
    QByteArrayData data[14];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JavaScriptOperations_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JavaScriptOperations_t qt_meta_stringdata_JavaScriptOperations = {
    {
QT_MOC_LITERAL(0, 0, 20), // "JavaScriptOperations"
QT_MOC_LITERAL(1, 21, 16), // "AddReaderReceive"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "char*"
QT_MOC_LITERAL(4, 45, 14), // "AddMainContent"
QT_MOC_LITERAL(5, 60, 7), // "display"
QT_MOC_LITERAL(6, 68, 3), // "val"
QT_MOC_LITERAL(7, 72, 9), // "SetReader"
QT_MOC_LITERAL(8, 82, 4), // "play"
QT_MOC_LITERAL(9, 87, 5), // "pause"
QT_MOC_LITERAL(10, 93, 4), // "stop"
QT_MOC_LITERAL(11, 98, 4), // "next"
QT_MOC_LITERAL(12, 103, 6), // "search"
QT_MOC_LITERAL(13, 110, 4) // "type"

    },
    "JavaScriptOperations\0AddReaderReceive\0"
    "\0char*\0AddMainContent\0display\0val\0"
    "SetReader\0play\0pause\0stop\0next\0search\0"
    "type"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JavaScriptOperations[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x0a /* Public */,
       4,    2,   64,    2, 0x0a /* Public */,
       5,    1,   69,    2, 0x0a /* Public */,
       7,    1,   72,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    0,   78,    2, 0x0a /* Public */,
      12,    2,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    2,    2,
    QMetaType::QString, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QVariantList, QMetaType::QString, QMetaType::QString,    6,   13,

       0        // eod
};

void JavaScriptOperations::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        JavaScriptOperations *_t = static_cast<JavaScriptOperations *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddReaderReceive((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 1: _t->AddMainContent((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2]))); break;
        case 2: { QString _r = _t->display((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->SetReader((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->play(); break;
        case 5: _t->pause(); break;
        case 6: _t->stop(); break;
        case 7: _t->next(); break;
        case 8: { QVariantList _r = _t->search((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE