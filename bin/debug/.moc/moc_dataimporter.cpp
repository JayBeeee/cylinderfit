/****************************************************************************
** Meta object code from reading C++ file 'dataimporter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/dataimporter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataimporter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataImporter_t {
    QByteArrayData data[8];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DataImporter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DataImporter_t qt_meta_stringdata_DataImporter = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 13),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 12),
QT_MOC_LITERAL(4, 41, 9),
QT_MOC_LITERAL(5, 51, 14),
QT_MOC_LITERAL(6, 66, 10),
QT_MOC_LITERAL(7, 77, 1)
    },
    "DataImporter\0sendDataReady\0\0sendErrorMsg\0"
    "importXYZ\0QList<Point3D>\0QIODevice*\0"
    "d\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataImporter[] = {

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
       1,    0,   29,    2, 0x06,
       3,    1,   30,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       4,    1,   33,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    0x80000000 | 5, 0x80000000 | 6,    7,

       0        // eod
};

void DataImporter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataImporter *_t = static_cast<DataImporter *>(_o);
        switch (_id) {
        case 0: _t->sendDataReady(); break;
        case 1: _t->sendErrorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { QList<Point3D> _r = _t->importXYZ((*reinterpret_cast< QIODevice*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<Point3D>*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QIODevice* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataImporter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataImporter::sendDataReady)) {
                *result = 0;
            }
        }
        {
            typedef void (DataImporter::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataImporter::sendErrorMsg)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject DataImporter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataImporter.data,
      qt_meta_data_DataImporter,  qt_static_metacall, 0, 0}
};


const QMetaObject *DataImporter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataImporter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataImporter.stringdata))
        return static_cast<void*>(const_cast< DataImporter*>(this));
    return QObject::qt_metacast(_clname);
}

int DataImporter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void DataImporter::sendDataReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DataImporter::sendErrorMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
