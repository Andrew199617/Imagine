/****************************************************************************
** Meta object code from reading C++ file 'DetailsLayout.h'
**
** Created: Fri Oct 21 15:27:34 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DetailsLayout.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DetailsLayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const qtuint qt_meta_data_DetailsLayout[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      31,   14,   14,   14, 0x08,
      52,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DetailsLayout[] = {
    "DetailsLayout\0\0ButtonPressed()\0"
    "CreateNewComponent()\0ResizeMenu()\0"
};

void DetailsLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DetailsLayout *_t = static_cast<DetailsLayout *>(_o);
        switch (_id) {
        case 0: _t->ButtonPressed(); break;
        case 1: _t->CreateNewComponent(); break;
        case 2: _t->ResizeMenu(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DetailsLayout::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DetailsLayout::staticMetaObject = {
    { &ImgnFrame::staticMetaObject, qt_meta_stringdata_DetailsLayout,
      qt_meta_data_DetailsLayout, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DetailsLayout::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DetailsLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DetailsLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DetailsLayout))
        return static_cast<void*>(const_cast< DetailsLayout*>(this));
    return ImgnFrame::qt_metacast(_clname);
}

int DetailsLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ImgnFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
