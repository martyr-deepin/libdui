/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

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
#include "dlistview.h"
#include "dboxwidget.h"

class IconItem : public DUI::DVBoxWidget
{
public:
    explicit IconItem(QWidget *parent = 0) :
        DUI::DVBoxWidget(parent)
    {
        icon = new QLabel;
        label = new QLabel;

        label->setWordWrap(true);

        layout()->addWidget(icon, 0, Qt::AlignHCenter);
        layout()->addWidget(label, 0 , Qt::AlignHCenter);
    }

public:
    QLabel *icon;
    QLabel *label;
};

class ItemDelegate : public DUI::DListItemDelegate
{
public:
    ItemDelegate(QObject *parent = 0) : DUI::DListItemDelegate(parent)
    {}

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        if(viewIsWrapping)
            DUI::DListItemDelegate::paint(painter, option, index);
        else
            QStyledItemDelegate::paint(painter, option, index);
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        if(!viewIsWrapping)
            return DUI::DListItemDelegate::sizeHint(option, index);

        Q_UNUSED(option);
        Q_UNUSED(index);

        QLabel label;

        label.setText(index.data().toString());
        label.setWordWrap(true);
        label.setMaximumWidth(100);
        label.adjustSize();

        QSize size = label.sizeHint();

        size.setWidth(qMin(label.maximumWidth(), size.width()));

        return QSize(100, size.height() + 60);
    }

    // editing
    QWidget *createWidget(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        if(!viewIsWrapping)
            return 0;

        Q_UNUSED(option);
        Q_UNUSED(index);

        QStyleOptionViewItem opt = option;

        initStyleOption(&opt, index);

        IconItem *item = new IconItem(parent);

        item->resize(option.rect.size());

        setWidgetData(item, index);

        return item;
    }

    void setWidgetData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        QStyleOptionViewItem opt;

        initStyleOption(&opt, index);

        IconItem *item = static_cast<IconItem*>(editor);

        if(!item)
            return;

        item->icon->setPixmap(opt.icon.pixmap(QSize(60, 60)));
        item->label->setMaximumWidth(100);
        item->label->setText(index.data().toString());
        item->label->adjustSize();
    }

    bool viewIsWrapping = true;
};

FlowWidgetListTab::FlowWidgetListTab(QWidget *parent) : QWidget(parent)
{
    DUI::DListView *listView = new DUI::DListView(this);
    QFileSystemModel *model = new QFileSystemModel(this);

    ItemDelegate *delegate = new ItemDelegate(listView);

    listView->setItemDelegate(delegate);
    listView->setSpacing(10);
    listView->setResizeMode(QListView::Adjust);
    listView->setCacheBuffer(50);
    listView->setModel(model);
    listView->setOrientation(QListView::LeftToRight, true);

    model->setRootPath("/");
    listView->setRootIndex(model->index("/"));

    connect(listView, &DUI::DListView::doubleClicked,
            this, [listView](const QModelIndex &index) {
        listView->setRootIndex(index);
    });

    QWidget *button_widget = new QWidget;
    QHBoxLayout *buttonLayout = new QHBoxLayout(button_widget);
    QPushButton *button_back = new QPushButton("^");
    QPushButton *button_switch = new QPushButton("switch view mode");

    connect(button_back, &QPushButton::clicked, listView, [listView] {
        listView->setRootIndex(listView->rootIndex().parent());
    });

    connect(button_switch, &QPushButton::clicked,
            button_switch, [listView, delegate] {
        if(listView->isWrapping()) {
            listView->setOrientation(QListView::TopToBottom, false);
            listView->clear();
        } else {
            listView->setOrientation(QListView::LeftToRight, true);
        }

        delegate->viewIsWrapping = listView->isWrapping();
    });

    buttonLayout->addWidget(button_back);
    buttonLayout->addWidget(button_switch);
    listView->addFooterWidget(button_widget);

    QVBoxLayout *main_layout = new QVBoxLayout(this);

    main_layout->setMargin(0);
    main_layout->setSpacing(0);

    main_layout->addWidget(listView);
}

