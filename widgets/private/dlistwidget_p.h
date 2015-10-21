#ifndef DLISTWIDGET_P_H
#define DLISTWIDGET_P_H

#include "dscrollarea_p.h"
#include "dlistwidget.h"

class QVBoxLayout;

DUI_BEGIN_NAMESPACE

class DListWidgetPrivate : public DScrollAreaPrivate
{
protected:
    DListWidgetPrivate(DListWidget *qq);
    ~DListWidgetPrivate();

private:
    void init();

    int itemWidth;
    int itemHeight;
    QVBoxLayout *layout;
    QList<QWidget*> widgetList;
    QList<int> checkedList;
    DListWidget::CheckMode checkMode;
    QWidget *mainWidget;
    int visibleCount;
    QMap<const QWidget*, bool> mapVisible;
    bool checkable;
    bool toggleable;
    bool enableVerticalScroll;

    D_DECLARE_PUBLIC(DListWidget)
};

DUI_END_NAMESPACE

#endif // DLISTWIDGET_P_H

