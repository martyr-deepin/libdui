#ifndef DLISTVIEW_P_H
#define DLISTVIEW_P_H

#include "dobject_p.h"
#include "dlistview.h"

DUI_BEGIN_NAMESPACE

class DListViewPrivate : public DObjectPrivate
{
protected:
    DListViewPrivate(DListView *qq);

    void init();

private:
    D_DECLARE_PUBLIC(DListView)
};

DUI_END_NAMESPACE

#endif // DLISTVIEW_P_H

