/****************************************************************************
** Meta object code from reading C++ file 'calculatorgridview.h'
**
** Created: Thu Dec 20 21:54:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calculator/calculatorgridview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calculatorgridview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CalculatorGridView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CalculatorGridView[] = {
    "CalculatorGridView\0\0trueDragging()\0"
};

void CalculatorGridView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CalculatorGridView *_t = static_cast<CalculatorGridView *>(_o);
        switch (_id) {
        case 0: _t->trueDragging(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CalculatorGridView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CalculatorGridView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_CalculatorGridView,
      qt_meta_data_CalculatorGridView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CalculatorGridView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CalculatorGridView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CalculatorGridView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalculatorGridView))
        return static_cast<void*>(const_cast< CalculatorGridView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int CalculatorGridView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
