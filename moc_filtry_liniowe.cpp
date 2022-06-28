/****************************************************************************
** Meta object code from reading C++ file 'filtry_liniowe.h'
**
** Created: Sat Mar 3 21:13:44 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "filtry_liniowe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filtry_liniowe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Filtry_Liniowe[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   15,   15,   15, 0x0a,
      48,   15,   15,   15, 0x0a,
      60,   15,   15,   15, 0x0a,
      67,   15,   15,   15, 0x0a,
      76,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Filtry_Liniowe[] = {
    "Filtry_Liniowe\0\0sigUpdateImage()\0"
    "jakaMaska(int)\0jakiFiltr()\0mask()\0"
    "cancel()\0czysc()\0"
};

const QMetaObject Filtry_Liniowe::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Filtry_Liniowe,
      qt_meta_data_Filtry_Liniowe, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Filtry_Liniowe::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Filtry_Liniowe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Filtry_Liniowe::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Filtry_Liniowe))
        return static_cast<void*>(const_cast< Filtry_Liniowe*>(this));
    return QWidget::qt_metacast(_clname);
}

int Filtry_Liniowe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sigUpdateImage(); break;
        case 1: jakaMaska((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: jakiFiltr(); break;
        case 3: mask(); break;
        case 4: cancel(); break;
        case 5: czysc(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Filtry_Liniowe::sigUpdateImage()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
