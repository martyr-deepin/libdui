#include "calendarview.h"
#include "dcalendardbus.h"

#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QMessageBox>

CalendarView::CalendarView(QWidget *parent) : QWidget(parent)
{
    m_DBusInter = new DCalendarDBus("com.deepin.api.LunarCalendar", "/com/deepin/api/LunarCalendar", QDBusConnection::sessionBus(), this);
    m_LunarCache = new QMap<QDate, CaLunarDayInfo>;

    const QStringList headerlist({tr("Sun"), tr("Mon"), tr("Tue"), tr("Wed"), tr("Thu"), tr("Fri"), tr("Sta")});
    QHBoxLayout *headerLayout = new QHBoxLayout;
    for (int i = 0; i != 7; ++i)
    {
        QLabel *label = new QLabel(headerlist.at(i));
        label->setObjectName("CalendarHeader");
        label->setAlignment(Qt::AlignCenter);
        headerLayout->addWidget(label);
    }
    headerLayout->setMargin(0);
    headerLayout->setSpacing(0);

    // cells grid
    QGridLayout *gridLayout = new QGridLayout;
    for (int r = 0; r != 6; ++r)
        for (int c = 0; c != 7; ++c) {
            QWidget *cell = new QWidget;
            cell->installEventFilter(this);
            cell->setFocusPolicy(Qt::ClickFocus);
            cell->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            gridLayout->addWidget(cell, r, c);
            m_cellList.append(cell);
        }
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(gridLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);
}

int CalendarView::getDateType(const QDate &date) const
{
    const int currentIndex = getDateIndex(date);
    const CaLunarDayInfo info = getCaLunarDayInfo(currentIndex);
    const int dayOfWeek = date.dayOfWeek();
    bool weekends = dayOfWeek == 6 || dayOfWeek == 7;
    bool isCurrentMonth = m_currentDate.month() == date.month();
    bool isFestival = !info.mSolarFestival.isEmpty() || !info.mLunarFestival.isEmpty();

    int resultFlag = 0;
    if (!isCurrentMonth)
        resultFlag |= SO_NotCurrentMonth;
    if (isFestival)
        resultFlag |= SO_Festival;
    if (weekends)
        resultFlag |= SO_Weekends;

    return resultFlag;
}

void CalendarView::setCurrentDate(const QDate &date)
{
    m_currentDate = date;

    const QDate firstDay(date.year(), date.month(), 1);
    const int daysOfCal = (firstDay.dayOfWeek() % 7) + date.day() - 1;
    const int y = date.dayOfWeek() % 7;
    const int x = daysOfCal / 7;
    const int currentIndex = x * 7 + y;

    for (int i(0); i != 42; ++i)
        m_days[i] = date.addDays(i - currentIndex);

    setSelectedCell(currentIndex);
}

void CalendarView::setLunarVisible(bool visible)
{
    int state = int(m_showState);

    if (visible)
        state |= ShowLunar;
    else
        state &= ~ShowLunar;

    m_showState = ShowState(state);
    update();
}

void CalendarView::setColorVisible(bool visible)
{
    int state = int(m_showState);

    if (visible)
        state |= ShowColor;
    else
        state &= ~ShowColor;

    m_showState = ShowState(state);
    update();
}

int CalendarView::getDateIndex(const QDate &date) const
{
    for (int i = 0; i != 42; ++i)
        if (m_days[i] == date)
            return i;

    return 0;
}

bool CalendarView::eventFilter(QObject *o, QEvent *e)
{
    QWidget *cell = qobject_cast<QWidget *>(o);

    if (cell && m_cellList.contains(cell)) {
        if (e->type() == QEvent::Paint) {
            paintCell(cell);
        } else if (e->type() == QEvent::MouseButtonRelease) {
            cellClicked(cell);
        }
    }

    return false;
}

const QString CalendarView::getCellDayNum(int pos)
{
    const QString result = QString::number(m_days[pos].day());

    if (m_showState & ShowLunar)
        return result + '\n';
    else
        return result;
}

const QString CalendarView::getLunarDetail(int pos)
{
    const QDate day = m_days[pos];

    bool o1;
    Q_UNUSED(o1)
    const QDBusReply<CaLunarDayInfo> reply = m_DBusInter->GetLunarInfoBySolar(day.year(), day.month(), day.day(), o1);
    const CaLunarDayInfo lunarInfo = reply.value();

    QString result;
    result = QString(tr("%1年%2%3").arg(lunarInfo.mGanZhiYear)
                                  .arg(lunarInfo.mLunarMonthName)
                                  .arg(lunarInfo.mLunarDayName));

    if (!lunarInfo.mSolarFestival.isEmpty())
        result += ' ' + lunarInfo.mSolarFestival;
    if (!lunarInfo.mLunarFestival.isEmpty())
        result += ' ' + lunarInfo.mLunarFestival;

    return result;
}

const QString CalendarView::getLunar(int pos)
{
    CaLunarDayInfo info = getCaLunarDayInfo(pos);

    if (info.mTerm.isEmpty())
        return info.mLunarDayName;
    return info.mTerm;
}

const CaLunarDayInfo CalendarView::getCaLunarDayInfo(int pos) const
{
    const QDate date = m_days[pos];

    if (m_LunarCache->contains(date))
        return m_LunarCache->value(date);
    if (m_LunarCache->size() > 1000)
        m_LunarCache->clear();

    bool o1;
    QDBusReply<CaLunarDayInfo> reply = m_DBusInter->GetLunarInfoBySolar(date.year(), date.month(), date.day(), o1);

    m_LunarCache->insert(date, reply.value());

    return reply.value();
}

void CalendarView::paintCell(QWidget *cell)
{
    const int pos = m_cellList.indexOf(cell);
    const int type = getDateType(m_days[pos]);
    const bool isSelectedCell = pos == m_selectedCell;
    QPainter painter(cell);

    // draw selected cell background circle
    if (isSelectedCell)
    {
        QRect fillRect = cell->rect();
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

        painter.setRenderHints(QPainter::HighQualityAntialiasing);

        painter.setBrush(QBrush(m_backgroundCircleColor));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(squareRect);
    }

    painter.setPen(Qt::SolidLine);

    // draw text of day
    if (isSelectedCell)
        painter.setPen(m_selectedTextColor);
    else
    {
        const int tType = type & 0xff;
        if (tType & SO_NotCurrentMonth)
            painter.setPen(m_notCurrentTextColor);
        else if (type == SO_Weekends)
            painter.setPen(m_weekendsTextColor);
        else
            painter.setPen(m_defaultTextColor);
    }
    painter.drawText(cell->rect(), Qt::AlignCenter, getCellDayNum(pos));

    // draw text of day type
    if (m_showState & ShowLunar)
    {
        if (isSelectedCell)
            painter.setPen(m_selectedLunarColor);
        else if (m_showState & ShowColor)
        {
            const int tType = type & 0xff;
            if (m_showState & ShowColor)
            {
                if (tType & SO_NotCurrentMonth)
                    painter.setPen(tType & SO_Festival ? m_festivalLunarColor : m_notCurrentLunarColor);
                else if (tType & SO_Festival)
                    painter.setPen(m_festivalLunarColor);
                else if (tType & SO_Weekends)
                    painter.setPen(m_weekendsLunarColor);
                else
                    painter.setPen(m_defaultLunarColor);
            } else
                painter.setPen(m_defaultLunarColor);
        }
        painter.drawText(cell->rect(), Qt::AlignCenter, '\n' + getLunar(pos));
    }

    painter.end();
}

void CalendarView::cellClicked(QWidget *cell)
{
    const int pos = m_cellList.indexOf(cell);
    if (pos == -1)
        return;

    setSelectedCell(pos);

    // my gift eggs
    static int gift = 0;
    if (m_days[pos] == QDate(1993, 7, 28))
        if (++gift == 10)
            QMessageBox::about(this, "LinuxDeepin", "by shibowen <sbw@sbw.so> :P");
}

void CalendarView::setSelectedCell(int index)
{
    if (m_selectedCell == index)
        return;

    const int prevPos = m_selectedCell;
    m_selectedCell = index;

    m_cellList.at(prevPos)->update();
    m_cellList.at(index)->update();

    emit dateSelected(m_days[index], getLunarDetail(index));
}

