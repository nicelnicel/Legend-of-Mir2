/****************************************************************************
** Meta object code from reading C++ file 'Cry.Signal.Service.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Interprocess/Cry.Signal.Service.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Cry.Signal.Service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Cry__Signal__Work_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cry__Signal__Work_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cry__Signal__Work_t qt_meta_stringdata_Cry__Signal__Work = {
    {
QT_MOC_LITERAL(0, 0, 17) // "Cry::Signal::Work"

    },
    "Cry::Signal::Work"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cry__Signal__Work[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Cry::Signal::Work::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Cry::Signal::Work::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Cry__Signal__Work.data,
      qt_meta_data_Cry__Signal__Work,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Cry::Signal::Work::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cry::Signal::Work::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cry__Signal__Work.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "std::enable_shared_from_this<Work>"))
        return static_cast< std::enable_shared_from_this<Work>*>(this);
    return QObject::qt_metacast(_clname);
}

int Cry::Signal::Work::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Cry__Signal__NetworkEngineService_t {
    QByteArrayData data[1];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cry__Signal__NetworkEngineService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cry__Signal__NetworkEngineService_t qt_meta_stringdata_Cry__Signal__NetworkEngineService = {
    {
QT_MOC_LITERAL(0, 0, 33) // "Cry::Signal::NetworkEngineSer..."

    },
    "Cry::Signal::NetworkEngineService"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cry__Signal__NetworkEngineService[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Cry::Signal::NetworkEngineService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Cry::Signal::NetworkEngineService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Cry__Signal__NetworkEngineService.data,
      qt_meta_data_Cry__Signal__NetworkEngineService,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Cry::Signal::NetworkEngineService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cry::Signal::NetworkEngineService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Cry__Signal__NetworkEngineService.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ServiceInterface"))
        return static_cast< ServiceInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int Cry::Signal::NetworkEngineService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
