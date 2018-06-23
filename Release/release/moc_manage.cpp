/****************************************************************************
** Meta object code from reading C++ file 'manage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../manage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Manage_t {
    QByteArrayData data[17];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Manage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Manage_t qt_meta_stringdata_Manage = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Manage"
QT_MOC_LITERAL(1, 7, 6), // "change"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 3), // "num"
QT_MOC_LITERAL(4, 19, 4), // "show"
QT_MOC_LITERAL(5, 24, 8), // "recreate"
QT_MOC_LITERAL(6, 33, 10), // "changetext"
QT_MOC_LITERAL(7, 44, 11), // "changetext2"
QT_MOC_LITERAL(8, 56, 14), // "setStartWindow"
QT_MOC_LITERAL(9, 71, 2), // "ai"
QT_MOC_LITERAL(10, 74, 12), // "start_normal"
QT_MOC_LITERAL(11, 87, 11), // "start_debug"
QT_MOC_LITERAL(12, 99, 9), // "showGrade"
QT_MOC_LITERAL(13, 109, 9), // "startGame"
QT_MOC_LITERAL(14, 119, 8), // "quitGame"
QT_MOC_LITERAL(15, 128, 8), // "gotoMenu"
QT_MOC_LITERAL(16, 137, 14) // "changeMusicVol"

    },
    "Manage\0change\0\0num\0show\0recreate\0"
    "changetext\0changetext2\0setStartWindow\0"
    "ai\0start_normal\0start_debug\0showGrade\0"
    "startGame\0quitGame\0gotoMenu\0changeMusicVol"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Manage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    0,   87,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    0,   90,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Manage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Manage *_t = static_cast<Manage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->show(); break;
        case 2: _t->recreate(); break;
        case 3: _t->changetext(); break;
        case 4: _t->changetext2(); break;
        case 5: _t->setStartWindow(); break;
        case 6: _t->ai(); break;
        case 7: _t->start_normal(); break;
        case 8: _t->start_debug(); break;
        case 9: _t->showGrade(); break;
        case 10: _t->startGame(); break;
        case 11: _t->quitGame(); break;
        case 12: _t->gotoMenu(); break;
        case 13: _t->changeMusicVol(); break;
        default: ;
        }
    }
}

const QMetaObject Manage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Manage.data,
      qt_meta_data_Manage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Manage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Manage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Manage.stringdata0))
        return static_cast<void*>(const_cast< Manage*>(this));
    return QObject::qt_metacast(_clname);
}

int Manage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
