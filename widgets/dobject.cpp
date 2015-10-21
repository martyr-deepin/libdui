#include "dobject.h"
#include "private/dobject_p.h"

DUI_BEGIN_NAMESPACE

DObjectPrivate::DObjectPrivate(DObject *qq):
    q_ptr(qq)
{

}

DObjectPrivate::~DObjectPrivate()
{

}

DObject::DObject(DObjectPrivate &dd):
    d_d_ptr(&dd)
{

}

DObject::~DObject()
{

}

DUI_END_NAMESPACE
