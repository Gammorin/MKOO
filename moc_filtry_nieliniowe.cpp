/****************************************************************************
** Meta object code from reading C++ file 'filtry_nieliniowe.h'
**
** Created: Sat Mar 3 21:13:45 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "filtry_nieliniowe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filtry_nieliniowe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Filtry_Nieliniowe[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   18,   18,   18, 0x0a,
      45,   18,   18,   18, 0x0a,
      55,   18,   18,   18, 0x0a,
      65,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Filtry_Nieliniowe[] = {
    "Filtry_Nieliniowe\0\0sigUpdateImage()\0"
    "cancel()\0maximum()\0minimum()\0mediana()\0"
};

const QMetaObject Filtry_Nieliniowe::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Filtry_Nieliniowe,
      qt_meta_data_Filtry_Nieliniowe, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Filtry_Nieliniowe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Filtry_Nieliniowe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Filtry_Nieliniowe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Filtry_Nieliniowe))
        return static_cast<void*>(const_cast< Filtry_Nieliniowe*>(this));
    return QWidget::qt_metacast(_clname);
}

int Filtry_Nieliniowe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigUpdateImage(); break;
        case 1: cancel(); break;
        case 2: maximum(); break;
        case 3: minimum(); break;
        case 4: mediana(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Filtry_Nieliniowe::sigUpdateImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
