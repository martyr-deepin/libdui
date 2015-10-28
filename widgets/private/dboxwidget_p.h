#ifndef DBOXWIDGET_P
#define DBOXWIDGET_P

#include "dobject_p.h"
#include "dboxwidget.h"

class QBoxLayout;

DUI_BEGIN_NAMESPACE

class DBoxWidgetPrivate : public DObjectPrivate
{
    DBoxWidgetPrivate(DBoxWidget *qq);

    QBoxLayout *layout;

    void init();

    Q_DECLARE_PUBLIC(DBoxWidget)
};

DUI_END_NAMESPACE

#endif // DBOXWIDGET_P
