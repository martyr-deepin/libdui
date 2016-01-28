#ifndef DFLOWLISTVIEW_P_H
#define DFLOWLISTVIEW_P_H

#include "dlistview_p.h"
#include "dflowlistview.h"

DUI_BEGIN_NAMESPACE

class DFlowListItemCreator;
class DFlowListViewPrivate : public DListViewPrivate
{
    DFlowListViewPrivate(DFlowListView *qq);
    ~DFlowListViewPrivate();

    void init();

    void onRowsInserted(const QModelIndex & parent, int first, int last);
    void onRowsAboutToBeRemoved(const QModelIndex & parent, int first, int last);
    void onDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight,
                          const QVector<int> & roles = QVector<int> ());
    void _q_updateIndexWidget();
    void _q_onItemPaint(const QStyleOptionViewItem &option, const QModelIndex &index);

    int cacheBuffer = 0;
    int cacheCount = 0;

    /// contain widget QModelIndex row number list.
    QMap<int, QWidget*> indexToWidgetMap;

    DFlowListItemCreator *creator = nullptr;

    D_DECLARE_PUBLIC(DFlowListView)
};

DUI_END_NAMESPACE

#endif // DFLOWLISTVIEW_P_H

