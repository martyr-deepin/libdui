#ifndef DLISTVIEW_P_H
#define DLISTVIEW_P_H

#include "dobject_p.h"
#include "dlistview.h"

DUI_BEGIN_NAMESPACE

class DListItemCreator;
class DBoxWidget;
class DListViewPrivate : public DObjectPrivate
{
    DListViewPrivate(DListView *qq);
    ~DListViewPrivate();

    void init();

    void onRowsInserted(const QModelIndex & parent, int first, int last);
    void onRowsAboutToBeRemoved(const QModelIndex & parent, int first, int last);
    void onDataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight,
                          const QVector<int> & roles = QVector<int> ());
    void onOrientationChanged();

    void _q_updateIndexWidget();
    void _q_onItemPaint(const QStyleOptionViewItem &option, const QModelIndex &index);

    int cacheBuffer = 0;
    int cacheCount = 0;

    /// Will be updated within the geometry QModelIndex.
    int startIndex = INT_MAX;
    int endIndex = -1;

    /// prevent q::paintEvent and _q_delayUpdateIndexWidget loop calls
    bool indexWidgetUpdated = false;

    /// contain widget QModelIndex row number list.
    QMap<int, QWidget*> indexToWidgetMap;
    DListItemCreator *creator = nullptr;
    DBoxWidget *headerLayout = nullptr;
    DBoxWidget *footerLayout = nullptr;

    QList<QWidget*> headerList;
    QList<QWidget*> footerList;

#if(QT_VERSION < 0x050500)
    int left = 0, top = 0, right = 0, bottom = 0; // viewport margin
#endif

    D_DECLARE_PUBLIC(DListView)
};

DUI_END_NAMESPACE

#endif // DLISTVIEW_P_H

