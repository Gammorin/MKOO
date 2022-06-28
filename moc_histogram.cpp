/****************************************************************************
** Meta object code from reading C++ file 'histogram.h'
**
** Created: Sat Mar 3 21:13:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "histogram.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'histogram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_histogram[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   28,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_histogram[] = {
    "histogram\0\0sigUpdateImage()\0image\0"
    "zczytaj(QImage*)\0"
};

const QMetaObject histogram::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_histogram,
      qt_meta_data_histogram, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &histogram::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *histogram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *histogram::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_histogram))
        return static_cast<void*>(const_cast< histogram*>(this));
    return QWidget::qt_metacast(_clname);
}

int histogram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigUpdateImage(); break;
        case 1: zczytaj((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void histogram::sigUpdateImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
