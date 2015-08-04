#ifndef DCALENDARMODEL_H
#define DCALENDARMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QPoint>
#include <QStyleOption>

class DCalendarModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum CalendarDayType
    {
        SO_Festival = QStyleOption::SO_CustomBase + 0x01,
        SO_Weekends = QStyleOption::SO_CustomBase + 0x10,
        SO_WeekendsAndFestival = SO_Festival | SO_Weekends,
        SO_Default,
    };

public:
    DCalendarModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void setDate(const QDate & date);
    int getDayNum(const QModelIndex & index) const;

signals:
    void selectedCellChanged(const QModelIndex & index);

public slots:

private:
    QPoint dateToCell(const QDate &date) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    // 转农历
    QString toLunar(const QDate & date, const QString & format = "MM月DD") const;

private:
    const QString headerList[7] = {tr("日"), tr("一"), tr("二"), tr("三"), tr("四"), tr("五"), tr("六")};
    const QString monthNameList[12] = {tr("正"), tr("二"), tr("三"), tr("四"), tr("五"), tr("六"), tr("七"), tr("八"), tr("九"), tr("十"), tr("冬"), tr("腊")};
    const QString dayNameList[30] = {tr("初一"), tr("初二"), tr("初三"), tr("初四"), tr("初五"), tr("初六"), tr("初七"), tr("初八"), tr("初九"), tr("初十"),
                                     tr("十一"), tr("十二"), tr("十三"), tr("十四"), tr("十五"), tr("十六"), tr("十七"), tr("十八"), tr("十九"), tr("二十"),
                                     tr("廿一"), tr("廿二"), tr("廿三"), tr("廿四"), tr("廿五"), tr("廿六"), tr("廿七"), tr("廿八"), tr("廿九"), tr("三十")};

    QDate days[42];
    QDate currentDate;
};

#endif // DCALENDARMODEL_H
