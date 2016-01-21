#ifndef DFLOWLAYOUT_P_H
#define DFLOWLAYOUT_P_H

#include "dobject_p.h"
#include "dflowlayout.h"

class QLayoutItem;

DUI_BEGIN_NAMESPACE

class DFlowLayoutPrivate : public DObjectPrivate
{
    DFlowLayoutPrivate(DFlowLayout *qq);

    QSize doLayout(const QRect &rect, bool testOnly) const;

    QList<QLayoutItem*> itemList;
    int horizontalSpacing = -1;
    int verticalSpacing = -1;
    mutable QSize sizeHint;

    D_DECLARE_PUBLIC(DFlowLayout)
};

DUI_END_NAMESPACE

#endif // DFLOWLAYOUT_P_H

