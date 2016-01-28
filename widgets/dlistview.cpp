#include "dthememanager.h"
#include "dscrollbar.h"
#include "dlistview.h"
#include "private/dlistview_p.h"

DUI_BEGIN_NAMESPACE

DListViewPrivate::DListViewPrivate(DListView *qq) :
    DObjectPrivate(qq)
{

}

void DListViewPrivate::init()
{
    D_Q(DListView);

    q->setVerticalScrollBar(new DScrollBar);
    q->setHorizontalScrollBar(new DScrollBar);
}

DListView::DListView(QWidget *parent) :
    QListView(parent),
    DObject(*new DListViewPrivate(this))
{
    D_THEME_INIT_WIDGET(DListView);

    d_func()->init();
}

DListView::DListView(DListViewPrivate &dd, QWidget *parent) :
    QListView(parent),
    DObject(dd)
{
    D_THEME_INIT_WIDGET(DListView);

    d_func()->init();
}

DUI_END_NAMESPACE
