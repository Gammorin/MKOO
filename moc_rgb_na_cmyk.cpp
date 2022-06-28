/****************************************************************************
** Meta object code from reading C++ file 'rgb_na_cmyk.h'
**
** Created: Sat Mar 3 21:13:40 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rgb_na_cmyk.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rgb_na_cmyk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rgb_na_cmyk[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   12,   12,   12, 0x0a,
      37,   12,   12,   12, 0x0a,
      57,   55,   48,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_rgb_na_cmyk[] = {
    "rgb_na_cmyk\0\0sigUpdateImage()\0cmyk()\0"
    "zresetuj()\0double\0,\0min(double,double)\0"
};

const QMetaObject rgb_na_cmyk::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_rgb_na_cmyk,
      qt_meta_data_rgb_na_cmyk, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rgb_na_cmyk::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rgb_na_cmyk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rgb_na_cmyk::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rgb_na_cmyk))
        return static_cast<void*>(const_cast< rgb_na_cmyk*>(this));
    return QWidget::qt_metacast(_clname);
}

int rgb_na_cmyk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigUpdateImage(); break;
        case 1: cmyk(); break;
        case 2: zresetuj(); break;
        case 3: { double _r = min((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void rgb_na_cmyk::sigUpdateImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
