#ifndef DSPINBOX_P_H
#define DSPINBOX_P_H

#include "dobject_p.h"
#include "dspinbox.h"

class QFrame;

DUI_BEGIN_NAMESPACE

class DSpinBoxPrivate : public DObjectPrivate
{
    DSpinBoxPrivate(DSpinBox *parent);

    void init();

    void _q_resizeInsideFrame(const QSize &size);

    QFrame *insideFrame;

    D_DECLARE_PUBLIC(DSpinBox)
};

class DDoubleSpinBoxPrivate : public DObjectPrivate
{
    DDoubleSpinBoxPrivate(DDoubleSpinBox *parent);

    void init();

    void _q_resizeInsideFrame(const QSize &size);

    QFrame *insideFrame;

    D_DECLARE_PUBLIC(DDoubleSpinBox)
};

DUI_END_NAMESPACE

#endif // DSPINBOX_P_H

