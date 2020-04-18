/****************************************************************************
** Meta object code from reading C++ file 'calculatorwindow.h'
**
** Created: Thu Dec 20 21:54:40 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "calculator/calculatorwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calculatorwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CalculatorWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      33,   31,   17,   17, 0x08,
      54,   17,   17,   17, 0x08,
      69,   17,   17,   17, 0x08,
      83,   17,   17,   17, 0x08,
      99,   17,   17,   17, 0x08,
     113,   17,   17,   17, 0x08,
     128,   17,   17,   17, 0x08,
     144,   17,   17,   17, 0x08,
     162,   17,   17,   17, 0x08,
     176,   17,   17,   17, 0x08,
     191,   17,   17,   17, 0x08,
     209,   17,   17,   17, 0x08,
     223,   17,   17,   17, 0x08,
     238,   17,   17,   17, 0x08,
     251,   17,   17,   17, 0x08,
     264,   17,   17,   17, 0x08,
     277,   17,   17,   17, 0x08,
     289,   17,   17,   17, 0x08,
     302,   17,   17,   17, 0x08,
     318,   17,   17,   17, 0x08,
     334,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CalculatorWindow[] = {
    "CalculatorWindow\0\0parseInput()\0,\0"
    "cellClicked(int,int)\0clearClicked()\0"
    "clickedGrid()\0clickedVector()\0"
    "clickedWire()\0clickedInput()\0"
    "clickedOutput()\0clickedInverter()\0"
    "clickedGate()\0clickedClock()\0"
    "clickedFlipFlop()\0clickedTick()\0"
    "clickedReset()\0clickedAdd()\0clickedSub()\0"
    "clickedAnd()\0clickedOr()\0clickedNot()\0"
    "clickedInsert()\0clickedRemove()\0"
    "clickedResult()\0"
};

void CalculatorWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CalculatorWindow *_t = static_cast<CalculatorWindow *>(_o);
        switch (_id) {
        case 0: _t->parseInput(); break;
        case 1: _t->cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->clearClicked(); break;
        case 3: _t->clickedGrid(); break;
        case 4: _t->clickedVector(); break;
        case 5: _t->clickedWire(); break;
        case 6: _t->clickedInput(); break;
        case 7: _t->clickedOutput(); break;
        case 8: _t->clickedInverter(); break;
        case 9: _t->clickedGate(); break;
        case 10: _t->clickedClock(); break;
        case 11: _t->clickedFlipFlop(); break;
        case 12: _t->clickedTick(); break;
        case 13: _t->clickedReset(); break;
        case 14: _t->clickedAdd(); break;
        case 15: _t->clickedSub(); break;
        case 16: _t->clickedAnd(); break;
        case 17: _t->clickedOr(); break;
        case 18: _t->clickedNot(); break;
        case 19: _t->clickedInsert(); break;
        case 20: _t->clickedRemove(); break;
        case 21: _t->clickedResult(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CalculatorWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CalculatorWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_CalculatorWindow,
      qt_meta_data_CalculatorWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CalculatorWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CalculatorWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CalculatorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CalculatorWindow))
        return static_cast<void*>(const_cast< CalculatorWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int CalculatorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
