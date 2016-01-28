#ifndef DLISTVIEW_H
#define DLISTVIEW_H

#include <QListView>

#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DListViewPrivate;
class DListView : public QListView, public DObject
{
public:
    explicit DListView(QWidget *parent = 0);

protected:
    DListView(DListViewPrivate &dd, QWidget *parent = 0);

private:
    D_DECLARE_PRIVATE(DListView)
};

DUI_END_NAMESPACE

#endif // DLISTVIEW_H
