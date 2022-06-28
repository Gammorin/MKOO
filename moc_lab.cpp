/****************************************************************************
** Meta object code from reading C++ file 'lab.h'
**
** Created: Sat Mar 3 21:13:43 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lab.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Lab[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,    4,    4,    4, 0x0a,
      40,    4,   33,    4, 0x0a,
      54,    4,   33,    4, 0x0a,
      68,    4,   33,    4, 0x0a,
      91,   88,   82,    4, 0x0a,
     119,  117,   82,    4, 0x0a,
     139,   88,   82,    4, 0x0a,
     165,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Lab[] = {
    "Lab\0\0sigUpdateImage()\0zresetuj()\0"
    "double\0funkX(double)\0funkY(double)\0"
    "funkZ(double)\0float\0,,\0funkX2(float,float,float)\0"
    ",\0funkY2(float,float)\0funkZ2(float,float,float)\0"
    "glowna_funkcja()\0"
};

const QMetaObject Lab::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Lab,
      qt_meta_data_Lab, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Lab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Lab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Lab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Lab))
        return static_cast<void*>(const_cast< Lab*>(this));
    return QWidget::qt_metacast(_clname);
}

int Lab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigUpdateImage(); break;
        case 1: zresetuj(); break;
        case 2: { double _r = funkX((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 3: { double _r = funkY((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 4: { double _r = funkZ((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 5: { float _r = funkX2((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 6: { float _r = funkY2((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 7: { float _r = funkZ2((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 8: glowna_funkcja(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Lab::sigUpdateImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
