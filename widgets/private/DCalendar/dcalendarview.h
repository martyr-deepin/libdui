#ifndef DCALENDARVIEW_H
#define DCALENDARVIEW_H

#include <QTableView>

class DCalendarView : public QTableView
{
    Q_OBJECT

public:
    DCalendarView(QWidget *parent);

signals:
    void cellClicked(const QModelIndex & index);

public slots:
    void currentChanged(const QModelIndex & current, const QModelIndex & previous);

private:
    void resizeEvent(QResizeEvent *e);
};

#endif // DCALENDARVIEW_H
