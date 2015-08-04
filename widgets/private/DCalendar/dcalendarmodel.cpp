#include "dcalendarmodel.h"

#include <QDebug>

DCalendarModel::DCalendarModel()
{
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
        return QString("%1\n").arg(days[listIndex].day(), 2, 10, QLatin1Char('0'));

    // the nongli day type
    if (role == Qt::WhatsThisRole)
        return '\n' + toLunar(days[listIndex], "DD");

    // day type (festival or weekends or ...)
    if (role == Qt::UserRole)
    {
        const int dayOfWeek = days[listIndex].dayOfWeek();
        if (dayOfWeek == 6 || dayOfWeek == 7)
            return SO_Weekends;
    }

    return QVariant();
}

void DCalendarModel::setDate(const QDate & date)
{
    currentDate = date;

    const QPoint p = dateToCell(date);
    const int currentIndex = p.x() * 7 + p.y();

    qDebug() << "current: " << p.x() << p.y();

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

QString DCalendarModel::toLunar(const QDate &date, const QString &format) const
{
    Q_UNUSED(date);

    QString result = format;

    result.replace("MM", "八");
    result.replace("DD", "十五");

    return std::move(result);
}

