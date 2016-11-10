/****************************************************************************
** Meta object code from reading C++ file 'CBDirectory.h'
**
** Created: Wed Nov 9 21:30:12 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "CBDirectory.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CBDirectory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const qtuint qt_meta_data_CBDirectory[] = {

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
      24,   13,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CBDirectory[] = {
    "CBDirectory\0\0objectName\0"
    "ShowFolderData(std::string)\0"
};

void CBDirectory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CBDirectory *_t = static_cast<CBDirectory *>(_o);
        switch (_id) {
        case 0: _t->ShowFolderData((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CBDirectory::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CBDirectory::staticMetaObject = {
    { &ImgnFrame::staticMetaObject, qt_meta_stringdata_CBDirectory,
      qt_meta_data_CBDirectory, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CBDirectory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CBDirectory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CBDirectory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBDirectory))
        return static_cast<void*>(const_cast< CBDirectory*>(this));
    return ImgnFrame::qt_metacast(_clname);
}

int CBDirectory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ImgnFrame::qt_metacall(_c, _id, _a);
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
