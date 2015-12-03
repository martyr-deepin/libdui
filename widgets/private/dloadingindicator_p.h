#ifndef DLOADINGINDICATOR_P
#define DLOADINGINDICATOR_P

#include "dloadingindicator.h"
#include "dobject_p.h"

DUI_BEGIN_NAMESPACE

class DLoadingIndicatorPrivate : public DObjectPrivate
{
    DLoadingIndicatorPrivate(DLoadingIndicator *qq);

    void init();
    void setLoadingItem(QGraphicsItem *item);

    QVariantAnimation rotateAni;
    bool loading;
    QWidget* widgetSource = NULL;
    bool smooth = false;
    DLoadingIndicator::RotationDirection direction = DLoadingIndicator::Clockwise;

    D_DECLARE_PUBLIC(DLoadingIndicator)
};

DUI_END_NAMESPACE

#endif // DLOADINGINDICATOR_P

