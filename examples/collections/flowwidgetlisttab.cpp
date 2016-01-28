#include <QPushButton>
#include <QTreeView>
#include <QLabel>
#include <QFileSystemModel>
#include <QStringListModel>
#include <QApplication>
#include <QPainter>

#include "flowwidgetlisttab.h"
#include "dflowlayout.h"
#include "anchors.h"
#include "dflowlistview.h"

class ItemDelegate : public DUI::DFlowListItemDelegate
{
public:
    ItemDelegate(QObject *parent = 0) : DUI::DFlowListItemDelegate(parent)
    {}

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        DUI::DFlowListItemDelegate::paint(painter, option, index);

        painter->setPen(Qt::red);
        painter->drawRect(option.rect);

//        QStyleOptionViewItem opt = option;

//        initStyleOption(&opt, index);

//        opt.icon.paint(painter, opt.rect);
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(option);
        Q_UNUSED(index);

        QLabel label;

        label.setText(index.data().toString());
        label.setWordWrap(true);
        label.setMaximumWidth(100);
        label.adjustSize();

        QSize size = label.sizeHint();

        size.setWidth(qMin(label.maximumWidth(), size.width()));

        return size;
    }

    // editing
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(option);
        Q_UNUSED(index);

        QLabel *label = new QLabel(parent);

        label->setWordWrap(true);
        label->setMaximumWidth(100);
        label->setText(index.data().toString());
        label->adjustSize();

        return label;
    }

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        QLabel *label = qobject_cast<QLabel*>(editor);

        if(!label)
            return;

        label->setText(index.data().toString());
        label->adjustSize();
    }
};

FlowWidgetListTab::FlowWidgetListTab(QWidget *parent) : QWidget(parent)
{
    DUI::DFlowListView *listView = new DUI::DFlowListView(this);
    QFileSystemModel *model = new QFileSystemModel(this);

    listView->setItemDelegate(new ItemDelegate(listView));
    listView->setSpacing(10);
    listView->setResizeMode(QListView::Adjust);
    listView->setCacheBuffer(50);
    listView->setModel(model);

    model->setRootPath("/");
    listView->setRootIndex(model->index("/"));

    connect(listView, &DUI::DFlowListView::doubleClicked,
            this, [listView](const QModelIndex &index) {
        listView->setRootIndex(index);
    });

    QHBoxLayout *main_layout = new QHBoxLayout(this);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);

    main_layout->addWidget(listView);
}

