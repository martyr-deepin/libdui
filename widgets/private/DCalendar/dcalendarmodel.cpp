#include "dcalendarmodel.h"

#include <QDebug>

DCalendarModel::DCalendarModel()
{
    mDBusInter = new DCalendarDBus("com.deepin.api.LunarCalendar", "/com/deepin/api/LunarCalendar", QDBusConnection::sessionBus(), this);
    mLunarCache = new QMap<QDate, CaLunarDayInfo>;
}

int DCalendarModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 6;
}

int DCalendarModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 7;
}

QVariant DCalendarModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    const int listIndex = index.row() * 7 + index.column();

    // the day number
    if (role == Qt::DisplayRole)
    {
        if (m_showLunar)
            return QString("%1\n").arg(days[listIndex].day(), 2, 10, QLatin1Char('0'));
        else
            return QString("%1").arg(days[listIndex].day(), 2, 10, QLatin1Char('0'));
    }

    // the nongli day type
    if (role == Qt::WhatsThisRole && m_showLunar)
        return '\n' + toLunar(days[listIndex]);

    // day type (festival or weekends or ...)
    if (role == Qt::UserRole)
    {
        const int dayOfWeek = days[listIndex].dayOfWeek();
        bool weekends = false;
        if (dayOfWeek == 6 || dayOfWeek == 7)
            weekends = true;

        CaLunarDayInfo info = getCaLunarDayInfo(days[listIndex]);
        if (!info.mTerm.isEmpty())
        {
            if (weekends)
                return SO_WeekendsAndFestival;
            else
                return SO_Festival;
        }

        if (weekends)
            return SO_Weekends;
        return SO_Default;
    }

    return QVariant();
}

void DCalendarModel::setDate(const QDate & date)
{
    currentDate = date;

    const QPoint p = dateToCell(date);
    const int currentIndex = p.x() * 7 + p.y();

    qDebug() << this << "current: " << p.x() << p.y();

    for (int i(0); i != 42; ++i)
        days[i] = date.addDays(i - currentIndex);

    emit dataChanged(index(1, 0), index(6, 6));
    emit selectedCellChanged(index(p.x(), p.y()));

#if 0
    QString buf = "";
    for (int i(0); i != 42; ++i)
    {
        if (i % 7 == 0)
            buf.append('\n');
        buf.append(QString::number(days[i].day())).append('\t');
    }
    qDebug() << buf.toStdString().c_str() << endl;
#endif
}

int DCalendarModel::getDayNum(const QModelIndex &index) const
{
    return days[index.row() * 7 + index.column()].day();
}

const QDate &DCalendarModel::getDate(const QModelIndex &index) const
{
    return days[index.row() * 7 + index.column()];
}

const CaLunarDayInfo DCalendarModel::getCaLunarDayInfo(const QDate &date) const
{
    if (mLunarCache->contains(date))
        return mLunarCache->value(date);
    if (mLunarCache->size() > MaxOfLunarCache)
        mLunarCache->clear();

    bool o1;
    QDBusReply<CaLunarDayInfo> reply = mDBusInter->GetLunarInfoBySolar(date.year(), date.month(), date.day(), o1);
    qDebug() << reply.isValid() << reply.error() << reply.value() << o1;

    mLunarCache->insert(date, reply.value());

    return reply.value();
}

QString DCalendarModel::getLunarDetail(const QModelIndex &index) const
{
    QDate date = getDate(index);
    CaLunarDayInfo lunarInfo = getCaLunarDayInfo(date);
    if (lunarInfo.mSolarFestival.isEmpty())
        return std::move(QString(tr("%1年%2%3").arg(lunarInfo.mGanZhiYear).arg(lunarInfo.mLunarMonthName).arg(lunarInfo.mLunarDayName)));
    return std::move(lunarInfo.mSolarFestival);
}

QPoint DCalendarModel::dateToCell(const QDate & date) const
{
    QPoint cell(0, 0);
    QDate firstDay(date.year(), date.month(), 1);

    //qDebug() << date << firstDay;

    cell.setY(date.dayOfWeek() % 7);

    int daysOfCal = (firstDay.dayOfWeek() % 7) + date.day() - 1;

    //qDebug() << "doc: " << daysOfCal;

    cell.setX(daysOfCal / 7);

    return cell;
}

QVariant DCalendarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return headerList[section];

    return QVariant();
}

QString DCalendarModel::toLunar(const QDate &date) const
{
    CaLunarDayInfo info = getCaLunarDayInfo(date);

    if (info.mTerm.isEmpty())
        return std::move(info.mLunarDayName);
    return std::move(info.mTerm);
}

