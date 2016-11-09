/****************************************************************************
** Meta object code from reading C++ file 'ImgnMainWindow.h'
**
** Created: Tue Nov 8 17:09:29 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ImgnMainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImgnMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const qtuint qt_meta_data_ImgnMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      35,   15,   15,   15, 0x08,
      49,   15,   15,   15, 0x08,
      61,   15,   15,   15, 0x08,
      71,   15,   15,   15, 0x08,
      83,   15,   15,   15, 0x08,
      94,   15,   15,   15, 0x08,
     114,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImgnMainWindow[] = {
    "ImgnMainWindow\0\0WindowsShowEvent()\0"
    "openingFile()\0AddObject()\0AddCube()\0"
    "AddSphere()\0AddPlane()\0OnPlayButtonPress()\0"
    "Save()\0"
};

void ImgnMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImgnMainWindow *_t = static_cast<ImgnMainWindow *>(_o);
        switch (_id) {
        case 0: _t->WindowsShowEvent(); break;
        case 1: _t->openingFile(); break;
        case 2: _t->AddObject(); break;
        case 3: _t->AddCube(); break;
        case 4: _t->AddSphere(); break;
        case 5: _t->AddPlane(); break;
        case 6: _t->OnPlayButtonPress(); break;
        case 7: _t->Save(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ImgnMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImgnMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ImgnMainWindow,
      qt_meta_data_ImgnMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImgnMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImgnMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImgnMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImgnMainWindow))
        return static_cast<void*>(const_cast< ImgnMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ImgnMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
