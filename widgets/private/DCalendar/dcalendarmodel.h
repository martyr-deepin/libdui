#ifndef DCALENDARMODEL_H
#define DCALENDARMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QPoint>
#include <QStyleOption>
#include <QMap>

#include "dcalendardbus.h"

class DCalendarModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum CalendarDayType
    {
        SO_Festival = QStyleOption::SO_CustomBase + 0x01,
        SO_Weekends = QStyleOption::SO_CustomBase + 0x02,
        SO_WeekendsAndFestival = SO_Festival | SO_Weekends,
        SO_NotCurrentMonth = 0x04,
        SO_NotCurrentMonthFestival = SO_NotCurrentMonth | SO_Festival,
        SO_Default,
    };

public:
    DCalendarModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void setDate(const QDate & date);
    int getDayNum(const QModelIndex & index) const;
    const QDate &getDate(const QModelIndex & index) const;
    const CaLunarDayInfo getCaLunarDayInfo(const QDate & date) const;
    QString getLunarDetail(const QDate &date) const;
    inline bool lunarVisible() const {return m_showLunar;}
    inline void setLunarVisible(const bool visible) {m_showLunar = visible;}

signals:
    void selectedCellChanged(const QModelIndex & index);

public slots:

private:
    QPoint dateToCell(const QDate &date) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    // 转农历
    QString toLunar(const QDate & date) const;

private:
    DCalendarDBus *mDBusInter;
    const QString headerList[7] = {tr("日"), tr("一"), tr("二"), tr("三"), tr("四"), tr("五"), tr("六")};

    QMap<QDate, CaLunarDayInfo> *mLunarCache = nullptr;

    QDate days[42];
    QDate currentDate;

    bool m_showLunar = true;

    static const int MaxOfLunarCache = 1024;
};

#endif // DCALENDARMODEL_H
