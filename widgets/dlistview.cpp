#include <QDebug>
#include <QScrollBar>

#include "dthememanager.h"
#include "dscrollbar.h"
#include "dlistview.h"
#include "private/dlistview_p.h"
#include "dflowlayout.h"

DUI_BEGIN_NAMESPACE

class DListItemCreator
{
public:
    explicit DListItemCreator();
    ~DListItemCreator();

    QWidget *creatWidget(const QStyleOptionViewItem &option, const QModelIndex &index);
    void destroyWidget(QWidget *widget);
    void setWidgetData(QWidget *widget, const QModelIndex &index);
    void updateWidgetGeometry(QWidget *widget,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
    void clear();

protected:
    QList<QWidget*> widgetList;
    QList<QWidget*> bufferList;

    DListView *view;

private:
    friend class DListView;
    friend class DListViewPrivate;
};

DVariantListModel::DVariantListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int DVariantListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return dataList.count();
}

QVariant DVariantListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    return dataList.value(index.row());
}

bool DVariantListModel::setData(const QModelIndex &index,
                                 const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < dataList.size()) {
        dataList.replace(index.row(), value);
        Q_EMIT dataChanged(index, index, QVector<int>() << role);

        return true;
    }

    return false;
}

bool DVariantListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count < 1 || row < 0 || row > rowCount(parent))
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        dataList.insert(row, QVariant());

    endInsertRows();

    return true;
}

bool DVariantListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        dataList.removeAt(row);

    endRemoveRows();

    return true;
}

DListItemCreator::DListItemCreator()
{

}

DListItemCreator::~DListItemCreator()
{
    clear();
}

QWidget *DListItemCreator::creatWidget(const QStyleOptionViewItem &option,
                                               const QModelIndex &index)
{
    QWidget *widget = 0;

    if(bufferList.isEmpty()) {
        widget = view->itemDelegate()->createWidget(view->viewport(), option, index);

        if(!widget)
            return 0;
    } else {
        widget = bufferList.takeFirst();
        setWidgetData(widget, index);
    }

    widgetList << widget;

    return widget;
}

void DListItemCreator::destroyWidget(QWidget *widget)
{
    if(!widget)
        return;

    widgetList.removeOne(widget);

    widget->hide();

    bufferList << widget;
}

void DListItemCreator::setWidgetData(QWidget *widget, const QModelIndex &index)
{
    view->itemDelegate()->setWidgetData(widget, index);
}

void DListItemCreator::updateWidgetGeometry(QWidget *widget,
                                                const QStyleOptionViewItem &option,
                                                const QModelIndex &index) const
{
    view->itemDelegate()->updateWidgetGeometry(widget, option, index);
}

void DListItemCreator::clear()
{
    widgetList << bufferList;

    while(!widgetList.isEmpty()) {
        QWidget *widget = widgetList.takeAt(0);

        widget->deleteLater();
    }

    bufferList.clear();
}

DListItemDelegate::DListItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *DListItemDelegate::createWidget(QWidget *,
                                             const QStyleOptionViewItem &,
                                             const QModelIndex &) const
{
    return 0;
}

void DListItemDelegate::setWidgetData(QWidget *, const QModelIndex &) const
{

}

void DListItemDelegate::updateWidgetGeometry(QWidget *widget,
                                                 const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
    Q_UNUSED(index)

    if(!widget)
        return;

    widget->move(option.rect.topLeft());
}

DListViewPrivate::DListViewPrivate(DListView *qq) :
    DObjectPrivate(qq)
{

}

DListViewPrivate::~DListViewPrivate()
{
    if(creator)
        delete creator;
}

void DListViewPrivate::init()
{
    D_Q(DListView);

    creator = new DListItemCreator;
    creator->view = q;

    q->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

void DListViewPrivate::onRowsInserted(const QModelIndex &parent,
                                             int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    Q_ASSERT(creator);
    D_Q(DListView);
}

void DListViewPrivate::onRowsAboutToBeRemoved(const QModelIndex &parent,
                                            int first, int last)
{
    Q_UNUSED(parent);
    Q_ASSERT(creator);
    D_Q(DListView);

    int rowCount = q->model()->rowCount(parent);

    for(int i = rowCount - last + first - 1; i < rowCount; ++i) {
        creator->destroyWidget(indexToWidgetMap.take(i));
    }
}

void DListViewPrivate::onDataChanged(const QModelIndex &topLeft,
                                            const QModelIndex &bottomRight,
                                            const QVector<int> &roles)
{
    Q_UNUSED(roles);
    Q_ASSERT(creator);
    D_Q(DListView);

    for(int i = topLeft.row(); i <= bottomRight.row(); ++i) {
        const QModelIndex &index = q->model()->index(i, 0, q->rootIndex());

        creator->setWidgetData(q->indexWidget(index), index);
    }
}

void DListViewPrivate::_q_updateIndexWidget()
{
    D_Q(DListView);

    const QList<int> &indexList = indexToWidgetMap.keys();

    for(int i : indexList) {
        const QModelIndex &index = q->model()->index(i, 0, q->rootIndex());
        const QRect &rect = q->visualRect(index);
        QWidget *widget = q->indexWidget(index);

        if(q->isActiveRect(rect)) {
            widget->setVisible(q->isVisualRect(rect));
        } else {
            creator->destroyWidget(widget);
            q->setIndexWidget(index, 0);
        }
    }

    for(int i = startIndex; i <= endIndex; ++i) {
        const QModelIndex &index = q->model()->index(i, 0, q->rootIndex());
        const QRect &rect = q->visualRect(index);
        QWidget *widget = q->indexWidget(index);

        if(!index.isValid()) {
            continue;
        }

        if(q->isActiveRect(rect)) {
            if(!widget) {
                QStyleOptionViewItem option;

                option.rect = rect;
                widget = creator->creatWidget(option, index);
                q->setIndexWidget(index, widget);
            } else {
                creator->setWidgetData(widget, index);
            }

            if(!widget)
                continue;

            if(q->isVisualRect(rect)) {
                QStyleOptionViewItem option;

                option.rect = rect;
                creator->updateWidgetGeometry(widget, option, index);
                widget->show();
            }
        } else if(widget) {
            creator->destroyWidget(widget);
            q->setIndexWidget(index, 0);
        }

        indexWidgetUpdated = true;
    }

    startIndex = INT_MAX;
    endIndex = -1;
}

void DListViewPrivate::_q_onItemPaint(const QStyleOptionViewItem &option,
                                          const QModelIndex &index)
{
    Q_UNUSED(option);

    if(index.row() < startIndex)
        startIndex = index.row();
    else if(index.row() > endIndex)
        endIndex = index.row();
}

DListView::DListView(QWidget *parent) :
    QListView(parent),
    DObject(*new DListViewPrivate(this))
{
    d_func()->init();
}

void DListView::setRootIndex(const QModelIndex &index)
{
    D_D(DListView);

    if(!index.isValid())
        return;

    const QList<int> &indexList = d->indexToWidgetMap.keys();

    for(int i : indexList) {
        d->creator->destroyWidget(d->indexToWidgetMap.take(i));
    }

    d->startIndex = INT_MAX;
    d->endIndex = -1;

    QListView::setRootIndex(index);
}

DListItemDelegate *DListView::itemDelegate() const
{
    return qobject_cast<DListItemDelegate*>(QListView::itemDelegate());
}

void DListView::setItemDelegate(DListItemDelegate *delegate)
{
    DListItemDelegate *old_delegate = itemDelegate();

    if(old_delegate)
        disconnect(old_delegate, SIGNAL(itemPaint(QStyleOptionViewItem,QModelIndex)),
                   this, SLOT(_q_onItemPaint(QStyleOptionViewItem,QModelIndex)));

    QListView::setItemDelegate(delegate);

    if(delegate)
        connect(delegate, SIGNAL(itemPaint(QStyleOptionViewItem,QModelIndex)),
                this, SLOT(_q_onItemPaint(QStyleOptionViewItem,QModelIndex)));
}

QWidget *DListView::getWidget(int index) const
{
    D_DC(DListView);

    return d->indexToWidgetMap.value(index);
}

QVariant DListView::getItemData(int index) const
{
    return model()->data(model()->index(index, 0, rootIndex()));
}

QModelIndex DListView::getIndexByWidget(const QWidget *widget) const
{
    D_DC(DListView);

    int index = d->indexToWidgetMap.key(const_cast<QWidget*>(widget), -1);

    return model()->index(index, 0, rootIndex());
}

bool DListView::isActiveRect(const QRect &rect) const
{
    D_DC(DListView);

    QRect area = viewport()->geometry();
    const int &cacheBuffer = d->cacheBuffer;

    area.adjust(-cacheBuffer, -cacheBuffer, cacheBuffer, cacheBuffer);

    return area.intersects(rect);
}

bool DListView::isVisualRect(const QRect &rect) const
{
    D_DC(DListView);

    const QRect &area = viewport()->geometry();

    return area.intersects(rect);
}

int DListView::cacheBuffer() const
{
    return d_func()->cacheBuffer;
}

int DListView::count() const
{
    return model()->rowCount(rootIndex());
}

void DListView::setIndexWidget(const QModelIndex &index, QWidget *widget)
{
    D_D(DListView);

    int row = index.row();

    if(widget) {
        widget->setParent(viewport());
        widget->show();
        d->indexToWidgetMap[row] = widget;
    } else {
        d->indexToWidgetMap.remove(row);
    }
}

bool DListView::addItem(const QVariant &data)
{
    return insertItem(count(), data);
}

bool DListView::addItems(const QVariantList &datas)
{
    return insertItems(count(), datas);
}

bool DListView::insertItem(int index, const QVariant &data)
{
    if(!model()->insertRow(index))
        return false;

    return model()->setData(model()->index(index, 0, rootIndex()), data);
}

bool DListView::insertItems(int index, const QVariantList &datas)
{
    if(!model()->insertRows(index, datas.count()))
        return false;

    for(int i = 0; i < datas.count(); ++i)
        model()->setData(model()->index(index + i, 0, rootIndex()), datas.at(i));

    return true;
}

bool DListView::removeItem(int index)
{
    return model()->removeRow(index);
}

bool DListView::removeItems(int index, int count)
{
    return model()->removeRows(index, count);
}

void DListView::clear()
{
    D_D(DListView);

    if(d->creator)
        d->creator->clear();

    d->indexToWidgetMap.clear();
}

void DListView::setCacheBuffer(int cacheBuffer)
{
    D_D(DListView);

    if (d->cacheBuffer == cacheBuffer)
        return;

    d->cacheBuffer = cacheBuffer;
    emit cacheBufferChanged(cacheBuffer);
}

void DListView::paintEvent(QPaintEvent *event)
{
    QListView::paintEvent(event);

    D_D(DListView);

    if(d->indexWidgetUpdated) {
        d->indexWidgetUpdated = false;
    } else {
        d->_q_updateIndexWidget();
    }
}

void DListView::dataChanged(const QModelIndex &topLeft,
                                const QModelIndex &bottomRight,
                                const QVector<int> &roles)
{
    QListView::dataChanged(topLeft, bottomRight, roles);
    d_func()->onDataChanged(topLeft, bottomRight, roles);
}

void DListView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    QListView::rowsInserted(parent, start, end);
    //d_func()->onRowsInserted(parent, start, end);
}

void DListView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    QListView::rowsAboutToBeRemoved(parent, start, end);
    d_func()->onRowsAboutToBeRemoved(parent, start, end);
}

#include "moc_dlistview.cpp"

DUI_END_NAMESPACE
