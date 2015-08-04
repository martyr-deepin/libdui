#include "dcalendardelegate.h"
#include "dcalendarmodel.h"

#include <QDebug>
#include <QPainter>
#include <QRect>

DCalendarDelegate::DCalendarDelegate(QWidget *parent)
    : QItemDelegate(parent)
{
}

void DCalendarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->fillRect(option.rect, m_backgroundColor);

    const bool isSelectedCell = option.state & QStyle::State_Selected;
    const DCalendarModel::CalendarDayType type = (DCalendarModel::CalendarDayType)index.data(Qt::UserRole).toInt();

    // draw selected cell background circle
    if (isSelectedCell)
    {
        QRect fillRect = option.rect;
        QRect squareRect = fillRect;
        if (fillRect.width() < fillRect.height())
        {
            squareRect.setTop(fillRect.top() + (fillRect.height() - fillRect.width()) / 2);
            squareRect.setWidth(fillRect.width());
            squareRect.setHeight(fillRect.width());
        }
        else
        {
            squareRect.setLeft(fillRect.left() + (fillRect.width() - fillRect.height()) / 2);
            squareRect.setWidth(fillRect.height());
            squareRect.setHeight(fillRect.height());
        }

        painter->setRenderHints(QPainter::HighQualityAntialiasing);

        painter->setBrush(QBrush(m_backgroundCircleColor));
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(squareRect);
    }

    painter->setPen(Qt::SolidLine);

    // draw text of day
    if (isSelectedCell)
        painter->setPen(m_selectedTextColor);
    else
        if (type == DCalendarModel::SO_Weekends)
            painter->setPen(m_weekendsTextColor);
        else
            painter->setPen(m_defaultTextColor);
    painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());

    // draw text of day type
    if (isSelectedCell)
        painter->setPen(m_selectedLunarColor);
    else
    {
        if (type == DCalendarModel::SO_Weekends)
            painter->setPen(m_weekendsLunarColor);
        else
            painter->setPen(m_defaultLunarColor);
    }
    painter->drawText(option.rect, Qt::AlignCenter, index.data(Qt::WhatsThisRole).toString());
    painter->restore();

    //return QItemDelegate::paint(painter, option, index);
}
