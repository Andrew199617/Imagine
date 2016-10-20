/****************************************************************************
** Meta object code from reading C++ file 'ImgnCreateComponent.h'
**
** Created: Tue Oct 18 10:56:02 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ImgnCreateComponent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImgnCreateComponent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const qtuint qt_meta_data_Imgn__ImgnCreateComponent[] = {

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
      27,   26,   26,   26, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Imgn__ImgnCreateComponent[] = {
    "Imgn::ImgnCreateComponent\0\0CreateClass()\0"
};

void Imgn::ImgnCreateComponent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImgnCreateComponent *_t = static_cast<ImgnCreateComponent *>(_o);
        switch (_id) {
        case 0: _t->CreateClass(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Imgn::ImgnCreateComponent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Imgn::ImgnCreateComponent::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Imgn__ImgnCreateComponent,
      qt_meta_data_Imgn__ImgnCreateComponent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Imgn::ImgnCreateComponent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Imgn::ImgnCreateComponent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Imgn::ImgnCreateComponent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Imgn__ImgnCreateComponent))
        return static_cast<void*>(const_cast< ImgnCreateComponent*>(this));
    return QWidget::qt_metacast(_clname);
}

int Imgn::ImgnCreateComponent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
