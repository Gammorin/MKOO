/****************************************************************************
** Meta object code from reading C++ file 'filtr_gaussa.h'
**
** Created: Sat Mar 3 21:13:43 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "filtr_gaussa.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filtr_gaussa.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Filtr_Gaussa[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   13,   13,   13, 0x0a,
      42,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Filtr_Gaussa[] = {
    "Filtr_Gaussa\0\0sigUpdateImage()\0"
    "zresetuj()\0oblicz()\0"
};

const QMetaObject Filtr_Gaussa::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Filtr_Gaussa,
      qt_meta_data_Filtr_Gaussa, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Filtr_Gaussa::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Filtr_Gaussa::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Filtr_Gaussa::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Filtr_Gaussa))
        return static_cast<void*>(const_cast< Filtr_Gaussa*>(this));
    return QWidget::qt_metacast(_clname);
}

int Filtr_Gaussa::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigUpdateImage(); break;
        case 1: zresetuj(); break;
        case 2: oblicz(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Filtr_Gaussa::sigUpdateImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
