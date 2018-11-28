/****************************************************************************
** Meta object code from reading C++ file 'Cry.FirstLication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Cry.FirstLication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Cry.FirstLication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QWindows__FirstLication_t {
    QByteArrayData data[12];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QWindows__FirstLication_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QWindows__FirstLication_t qt_meta_stringdata_QWindows__FirstLication = {
    {
QT_MOC_LITERAL(0, 0, 23), // "QWindows::FirstLication"
QT_MOC_LITERAL(1, 24, 10), // "SendNotify"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "uint32_t"
QT_MOC_LITERAL(4, 45, 4), // "uMsg"
QT_MOC_LITERAL(5, 50, 11), // "const void*"
QT_MOC_LITERAL(6, 62, 5), // "pData"
QT_MOC_LITERAL(7, 68, 5), // "uSize"
QT_MOC_LITERAL(8, 74, 10), // "PostNotify"
QT_MOC_LITERAL(9, 85, 25), // "google::protobuf::Message"
QT_MOC_LITERAL(10, 111, 6), // "OnSend"
QT_MOC_LITERAL(11, 118, 8) // "OnNotify"

    },
    "QWindows::FirstLication\0SendNotify\0\0"
    "uint32_t\0uMsg\0const void*\0pData\0uSize\0"
    "PostNotify\0google::protobuf::Message\0"
    "OnSend\0OnNotify"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWindows__FirstLication[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       8,    2,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   46,    2, 0x09 /* Protected */,
      11,    3,   47,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 3,    4,    6,    7,
    QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 9,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 3,    4,    6,    7,

       0        // eod
};

void QWindows::FirstLication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FirstLication *_t = static_cast<FirstLication *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->SendNotify((*reinterpret_cast< const uint32_t(*)>(_a[1])),(*reinterpret_cast< const void*(*)>(_a[2])),(*reinterpret_cast< const uint32_t(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->PostNotify((*reinterpret_cast< const uint32_t(*)>(_a[1])),(*reinterpret_cast< const google::protobuf::Message(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->OnSend(); break;
        case 3: { bool _r = _t->OnNotify((*reinterpret_cast< const uint32_t(*)>(_a[1])),(*reinterpret_cast< const void*(*)>(_a[2])),(*reinterpret_cast< const uint32_t(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef bool (FirstLication::*_t)(const uint32_t , const void * , const uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirstLication::SendNotify)) {
                *result = 0;
                return;
            }
        }
        {
            typedef bool (FirstLication::*_t)(const uint32_t , const google::protobuf::Message & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FirstLication::PostNotify)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QWindows::FirstLication::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QWindows__FirstLication.data,
      qt_meta_data_QWindows__FirstLication,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QWindows::FirstLication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWindows::FirstLication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QWindows__FirstLication.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Cry::Action::UnknownInterfaceEx"))
        return static_cast< Cry::Action::UnknownInterfaceEx*>(this);
    return QWidget::qt_metacast(_clname);
}

int QWindows::FirstLication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
bool QWindows::FirstLication::SendNotify(const uint32_t _t1, const void * _t2, const uint32_t _t3)
{
    bool _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
bool QWindows::FirstLication::PostNotify(const uint32_t _t1, const google::protobuf::Message & _t2)
{
    bool _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
