#ifndef DSPINBOX_P_H
#define DSPINBOX_P_H

#include "dobject_p.h"
#include "dspinbox.h"

class QFrame;
class QLabel;

DUI_BEGIN_NAMESPACE

class DImageButton;
class DSpinBoxPrivate : public DObjectPrivate
{
    DSpinBoxPrivate(DSpinBox *parent);

    void init();

    void _q_resizeInsideFrame(const QSize &size);

    QFrame *insideFrame;
    bool alert = false;
    int defaultValue = 0;

    D_DECLARE_PUBLIC(DSpinBox)
};

class DDoubleSpinBoxPrivate : public DObjectPrivate
{
    DDoubleSpinBoxPrivate(DDoubleSpinBox *parent);

    void init();

    void _q_resizeInsideFrame(const QSize &size);

    QFrame *insideFrame;
    bool alert = false;
    double defaultValue = 0;

    D_DECLARE_PUBLIC(DDoubleSpinBox)
};

DUI_END_NAMESPACE

#endif // DSPINBOX_P_H

