#include <QWidget>
#include <QVBoxLayout>
#include <QEvent>
#include <QDebug>

#include "dthememanager.h"
#include "dlistwidget.h"
#include "private/dlistwidget_p.h"

DUI_BEGIN_NAMESPACE

DListWidgetPrivate::DListWidgetPrivate(DListWidget *qq):
        DScrollAreaPrivate(qq),
        itemWidth(-1),
        itemHeight(-1),
        checkMode(DListWidget::Radio),
        mainWidget(new DBoxWidget(QBoxLayout::TopToBottom)),
        visibleCount(0),
        checkable(false),
        toggleable(false),
        enableHorizontalScroll(false),
        enableVerticalScroll(false)
{

}

DListWidgetPrivate::~DListWidgetPrivate()
{

}

void DListWidgetPrivate::init()
{
    Q_Q(DListWidget);

    mainWidget->setObjectName("MainWidget");

    q->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setAlignment(Qt::AlignHCenter);
    q->setWidget(mainWidget);

    QObject::connect(mainWidget, &DBoxWidget::sizeChanged, q, &DListWidget::updateSize);
}

DListWidget::DListWidget(CheckMode checkMode, QWidget *parent) :
    DScrollArea(*new DListWidgetPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(DListWidget);

    d_func()->checkMode = checkMode;
    d_func()->init();
}

DListWidget::DListWidget(QBoxLayout::Direction direction, DListWidget::CheckMode checkMode, QWidget *parent) :
    DScrollArea(*new DListWidgetPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(DListWidget);

    d_func()->mainWidget->setDirection(direction);
    d_func()->checkMode = checkMode;
    d_func()->init();
}

int DListWidget::addWidget(QWidget *w, Qt::Alignment a)
{
    insertWidget(-1, w, a);

    return count()-1;
}

void DListWidget::addWidgets(const QList<QWidget*> &ws, Qt::Alignment a)
{
    insertWidgets(-1, ws, a);
}

void DListWidget::insertWidget(int index, QWidget *w, Qt::Alignment a)
{
    Q_D(DListWidget);

    if(w==NULL || d->widgetList.contains(w))
        return;

    if(d->itemWidth>0){
        w->setFixedWidth(d->itemWidth);
    }

    if(d->itemHeight>0){
        w->setFixedHeight(d->itemHeight);
    }

    if(index < 0) {
        d->widgetList << w;
        d->mainWidget->layout()->addWidget(w, 0, a);
    } else {
        d->widgetList.insert(index, w);
        d->mainWidget->layout()->insertWidget(index, w, 0, a);
    }

    if(d->checkable)
        w->installEventFilter(this);

    d->mapVisible[w] = true;

    setVisibleCount(d->visibleCount + 1);

    emit countChanged(count());
}

void DListWidget::insertWidgets(int index, const QList<QWidget*> &ws, Qt::Alignment a)
{
    if(index < 0) {
        foreach (QWidget *w, ws) {
            insertWidget(-1, w, a);
        }
    } else {
        foreach (QWidget *w, ws) {
            insertWidget(index++, w, a);
        }
    }
}

void DListWidget::setItemSize(int w, int h)
{
    Q_D(DListWidget);

    d->itemWidth = w;
    d->itemHeight = h;

    if(d->itemWidth <= 0 && d->itemHeight <= 0)
        return;

    foreach (QWidget *w, d->widgetList) {
        if(d->itemWidth>0)
            w->setFixedWidth(d->itemWidth);
        if(d->itemHeight>0){
            w->setFixedHeight(d->itemHeight);
        }
    }
}

void DListWidget::clear(bool isDelete)
{
    Q_D(DListWidget);

    for(int i=0;i<count();++i){
        d->mainWidget->layout()->removeItem(d->mainWidget->layout()->takeAt(i));
        d->widgetList[i]->removeEventFilter(this);
        d->widgetList[i]->setParent(NULL);
        if(isDelete)
            d->widgetList[i]->deleteLater();
    }

    d->mapVisible.clear();
    d->widgetList.clear();
    d->checkedList.clear();

    resize(0, 0);
    setVisibleCount(0);

    emit countChanged(count());
}

void DListWidget::removeWidget(int index, bool isDelete)
{
    Q_D(DListWidget);

    QWidget *w = getWidget(index);

    d->widgetList.removeAt(index);
    d->mainWidget->layout()->removeItem(d->mainWidget->layout()->takeAt(index));
    d->checkedList.removeOne(index);

    if(d->mapVisible.value(w, false)){
        setVisibleCount(d->visibleCount -1);
    }
    d->mapVisible.remove(w);

    w->removeEventFilter(this);
    w->setParent(NULL);
    if(isDelete)
        w->deleteLater();

    emit countChanged(count());
}

void DListWidget::showWidget(int index)
{
    Q_D(DListWidget);

    QWidget *w = getWidget(index);

    if(!d->mapVisible.value(w, true)){
        w->show();
        d->mapVisible[w] = true;
        setVisibleCount(d->visibleCount+1);
    }
}

void DListWidget::hideWidget(int index)
{
    Q_D(DListWidget);

    QWidget *w = getWidget(index);

    if(d->mapVisible.value(w, false)){
        w->hide();
        d->mapVisible[w] = false;
        setVisibleCount(d->visibleCount-1);
    }
}

void DListWidget::setChecked(int index, bool checked)
{
    Q_D(DListWidget);

    if (!d->checkable || (checked && isChecked(index)) || (!checked && !isChecked(index)))
        return;

    if(d->checkMode == Radio && checked){
        int checkedWidget = firstChecked();
        if(checkedWidget>=0){
            getWidget(checkedWidget)->setProperty("checked", false);
            d->checkedList.removeOne(checkedWidget);
        }
    }

    if(index>=0 && index < count()){
        QWidget *w = getWidget(index);
        w->setProperty("checked", checked);
    }

    if(checked){
        d->checkedList << index;
    }else{
        d->checkedList.removeOne(index);
    }

    if(d->checkMode == Radio && checked){
        emit firstCheckedChanged(index);
    }

    emit checkedChanged(index, checked);
}

void DListWidget::setCheckMode(DListWidget::CheckMode checkMode)
{
    Q_D(DListWidget);

    d->checkMode = checkMode;
}

void DListWidget::setCheckable(bool checkable)
{
    Q_D(DListWidget);

    if (d->checkable == checkable)
        return;

    d->checkable = checkable;

    if(checkable){
        foreach (QWidget *w, d->widgetList) {
            w->installEventFilter(this);
        }
    }else{
        foreach (QWidget *w, d->widgetList) {
            w->removeEventFilter(this);
        }
    }
}

void DListWidget::setToggleable(bool enableUncheck)
{
    Q_D(DListWidget);

    if (d->toggleable == enableUncheck)
        return;

    d->toggleable = enableUncheck;
    emit toggleableChanged(enableUncheck);
}

void DListWidget::setEnableHorizontalScroll(bool enableHorizontalScroll)
{
    Q_D(DListWidget);

    if (d->enableHorizontalScroll == enableHorizontalScroll)
        return;

    d->enableHorizontalScroll = enableHorizontalScroll;

    updateSize();

    emit enableHorizontalScrollChanged(enableHorizontalScroll);
}

void DListWidget::setEnableVerticalScroll(bool enableVerticalScroll)
{
    Q_D(DListWidget);

    if (d->enableVerticalScroll == enableVerticalScroll)
        return;

    d->enableVerticalScroll = enableVerticalScroll;

    updateSize();

    emit enableVerticalScrollChanged(enableVerticalScroll);
}

int DListWidget::count() const
{
    Q_D(const DListWidget);

    return d->widgetList.count();
}

int DListWidget::indexOf(const QWidget* w)
{
    Q_D(DListWidget);

    return d->widgetList.indexOf(const_cast<QWidget*>(w));
}

QWidget *DListWidget::getWidget(int index) const
{
    Q_D(const DListWidget);

    return d->widgetList[index];
}

int DListWidget::firstChecked() const
{
    Q_D(const DListWidget);

    return d->checkedList.count()>0 ? d->checkedList.first() : -1;
}

QList<int> DListWidget::checkedList() const
{
    Q_D(const DListWidget);

    return d->checkedList;
}

bool DListWidget::checkable() const
{
    Q_D(const DListWidget);

    return d->checkable;
}

bool DListWidget::toggleable() const
{
    Q_D(const DListWidget);

    return d->toggleable;
}

bool DListWidget::isChecked(int index) const
{
    Q_D(const DListWidget);

    return d->checkedList.contains(index);
}

int DListWidget::visibleCount() const
{
    Q_D(const DListWidget);

    return d->visibleCount;
}

DListWidget::CheckMode DListWidget::checkMode() const
{
    Q_D(const DListWidget);

    return d->checkMode;
}

bool DListWidget::eventFilter(QObject *obj, QEvent *e)
{
    Q_D(DListWidget);

    if(!d->checkable || e->type() != QEvent::MouseButtonRelease)
        return false;

    QWidget *w = qobject_cast<QWidget*>(obj);

    if(w){
        int index = indexOf(w);
        if(index>=0){
            if(d->toggleable)
                setChecked(index, !isChecked(index));
            else
                setChecked(index, true);

            emit clicked(index);
        }
    }

    return false;
}

QSize DListWidget::sizeHint() const
{
    Q_D(const DListWidget);

    QSize size;
    size.setWidth(d->mainWidget->width());
    if(d->enableVerticalScroll)
        size.setHeight(qMin(maximumHeight(), d->mainWidget->height()));
    else
        size.setHeight(d->mainWidget->height());

    return size;
}

void DListWidget::setVisibleCount(int count)
{
    Q_D(DListWidget);

    if(d->visibleCount == count)
        return;

    d->visibleCount = count;

    emit visibleCountChanged(count);
}

void DListWidget::updateSize()
{
    Q_D(DListWidget);

    if(!d->enableHorizontalScroll) {
        setFixedWidth(d->mainWidget->width());
    } else {
        setMinimumWidth(0);
        resize(d->mainWidget->width(), height());
    }

    if(!d->enableVerticalScroll) {
        setFixedHeight(d->mainWidget->height());
    } else {
        setMinimumHeight(0);
        resize(width(), d->mainWidget->height());
    }

    updateGeometry();
}

QList<QWidget*> DListWidget::widgetList() const
{
    Q_D(const DListWidget);

    return d->widgetList;
}

QSize DListWidget::itemSize() const
{
    Q_D(const DListWidget);

    return QSize(d->itemWidth, d->itemHeight);
}

bool DListWidget::enableHorizontalScroll() const
{
    Q_D(const DListWidget);

    return d->enableHorizontalScroll;
}

bool DListWidget::enableVerticalScroll() const
{
    Q_D(const DListWidget);

    return d->enableVerticalScroll;
}

DListWidget::DListWidget(DListWidgetPrivate &dd, QWidget *parent):
    DScrollArea(dd, parent)
{
    D_THEME_INIT_WIDGET(DListWidget);

    d_func()->init();
}

DUI_END_NAMESPACE
