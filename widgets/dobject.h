#ifndef DOBJECT_H
#define DOBJECT_H

#include <QScopedPointer>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

#define D_DECLARE_PRIVATE(Class) Q_DECLARE_PRIVATE_D(qGetPtrHelper(d_d_ptr),Class)
#define D_DECLARE_PUBLIC(Class) Q_DECLARE_PUBLIC(Class)

class DObjectPrivate;
class DObject
{
protected:
    DObject(DObjectPrivate &dd);
    virtual ~DObject();

    QScopedPointer<DObjectPrivate> d_d_ptr;

    Q_DISABLE_COPY(DObject)
    D_DECLARE_PRIVATE(DObject)
};

DUI_END_NAMESPACE

#endif // DOBJECT_H
