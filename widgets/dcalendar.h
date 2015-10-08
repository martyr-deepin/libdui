#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDate>
#include <QSize>
#include <QPropertyAnimation>

#include "libdui_global.h"
#include "dlinkbutton.h"
#include "dimagebutton.h"

class CaLunarDayInfo;
class CalendarView;

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DCalendar : public QWidget
{
    Q_OBJECT

public:
    enum SelectionMode {
        NoSelection = 0,
        SingleSelection = 1,
    };

public:
    explicit DCalendar(QWidget *parent = 0);
    ~DCalendar();

    inline QDate getCurrentDate() const {return m_currentDate;}
    inline QDate getSelectDate() const {return m_showDate;}
    inline void setAnimationDuration(const int duration) {m_animation->setDuration(duration);}
    inline void setAnimationEasingCurve(const QEasingCurve curve) {m_animation->setEasingCurve(curve);}

signals:
    void selectedDateChanged(const QDate & date);

public slots:
    void setResetButtonText(const QString & resetText);
    void setCurrentDate(const QDate &date);
    void selectDate(const QDate &date);
    void setControlPanelVisible(bool visible);
    void setDateInfoVisible(bool visible);
    void setLunarVisible(bool visible);
    void setLunarFestivalHighlight(bool highlight);
    void setSelectionMode(SelectionMode mode);
    void updateCurrentDate();

private:
    bool eventFilter(QObject *o, QEvent *e);

private slots:
    void showEvent(QEvent *);
    void viewDateChanged(const QDate &date, const CaLunarDayInfo &detail);
    void aniToPrev();
    void aniToNext();

private:
    QLabel *m_detailLabel;
    QLabel *m_solarLabel;
    QLabel *m_lunarLabel;
    QLineEdit *m_yearEdt;
    QLineEdit *m_monEdt;
    DLinkButton *m_resetBtn;

    CalendarView *m_viewLeft;
    CalendarView *m_viewRight;
    CalendarView *m_viewCurrent;

    QWidget *m_topControlPanel;
    QWidget *m_solarLunarWidget;
    QWidget *m_viewOuterWidget;
    QWidget *m_viewInnerWidget;

    QPropertyAnimation *m_animation;

    QSize m_viewSize;
    QDate m_currentDate;
    QDate m_showDate;
};

DUI_END_NAMESPACE

#endif // CALENDARWIDGET_H
