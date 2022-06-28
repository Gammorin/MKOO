/****************************************************************************
** Meta object code from reading C++ file 'cie.h'
**
** Created: Sat Mar 3 21:13:42 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cie.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cie.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CIE[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,    4,    4,    4, 0x0a,
      39,    4,    4,    4, 0x0a,
      56,    4,    4,    4, 0x0a,
      68,    4,    4,    4, 0x0a,
      80,    4,    4,    4, 0x0a,
     101,   98,   92,    4, 0x0a,
     126,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CIE[] = {
    "CIE\0\0sigUpdateImage()\0konwersja_sRGB()\0"
    "konwersja_aRGB()\0ustawX(int)\0ustawY(int)\0"
    "ustawZ(int)\0float\0,,\0od_do(float,float,float)\0"
    "zresetuj()\0"
};

const QMetaObject CIE::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CIE,
      qt_meta_data_CIE, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CIE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CIE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CIE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CIE))
        return static_cast<void*>(const_cast< CIE*>(this));
    return QWidget::qt_metacast(_clname);
}

int CIE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigUpdateImage(); break;
        case 1: konwersja_sRGB(); break;
        case 2: konwersja_aRGB(); break;
        case 3: ustawX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: ustawY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: ustawZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { float _r = od_do((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 7: zresetuj(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CIE::sigUpdateImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
