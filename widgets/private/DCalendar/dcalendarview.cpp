#include "dcalendarview.h"

#include <QDebug>
#include <QHeaderView>

DCalendarView::DCalendarView(QWidget *parent)
    : QTableView(parent)
{
    setTabKeyNavigation(false);
    setShowGrid(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setVisible(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(SingleSelection);
    setFrameStyle(QFrame::NoFrame);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionsClickable(false);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionsClickable(false);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void DCalendarView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    //qDebug() << "currentChanged: " << current << previous;

    emit cellClicked(current);
}

void DCalendarView::resizeEvent(QResizeEvent *e)
{
    QTableView::resizeEvent(e);
}

