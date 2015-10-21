#ifndef DOBJECT_P_H
#define DOBJECT_P_H

#include "libdui_global.h"
#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DObjectPrivate
{
public:
    virtual ~DObjectPrivate();

protected:
    DObjectPrivate(DObject *qq);

    DObject *q_ptr;

    Q_DECLARE_PUBLIC(DObject)
};

DUI_END_NAMESPACE

#endif // DOBJECT_P_H

