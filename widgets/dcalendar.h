#ifndef DCALENDAR_H
#define DCALENDAR_H

#include <QDate>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QPropertyAnimation>

#include "libdui_global.h"
#include "dtextbutton.h"
#include "dimagebutton.h"

class DCalendarView;
class DCalendarDelegate;
class DCalendarModel;

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DCalendar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor backgroundCircleColor READ getBackgroundCircleColor WRITE setBackgroundCircleColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor defaultTextColor READ getDefaultTextColor WRITE setDefaultTextColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor weekendsTextColor READ getWeekendsTextColor WRITE setWeekendsTextColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor selectedTextColor READ getSelectedTextColor WRITE setSelectedTextColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor festivalTextColor READ getFestivalTextColor WRITE setFestivalTextColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor defaultLunarColor READ getDefaultLunarColor WRITE setDefaultLunarColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor weekendsLunarColor READ getWeekendsLunarColor WRITE setWeekendsLunarColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor selectedLunarColor READ getSelectedLunarColor WRITE setSelectedLunarColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor festivalLunarColor READ getFestivalLunarColor WRITE setFestivalLunarColor DESIGNABLE true SCRIPTABLE true)

public:
    explicit DCalendar(QWidget *parent = 0);
    ~DCalendar();

    inline QDate getCurrentDate() const {return currentDate;}
    inline QDate getSelectDate() const {return selectDate;}

    void animationToPrev();
    void animationToNext();
    inline void setAnimationDuration(const int duration) {m_animation->setDuration(duration);}
    inline void setAnimationEasingCurve(const QEasingCurve curve) {m_animation->setEasingCurve(curve);}

    inline bool lunarVisible() const {return m_lunarVisible;}
    void setLunarVisible(const bool visible);

    void resetCurrentDate(const QDate &resetDate);

    void setBackgroundColor(const QColor & color);
    QColor getBackgroundColor() const;
    void setBackgroundCircleColor(const QColor & color);
    QColor getBackgroundCircleColor() const;
    void setDefaultTextColor(const QColor & color);
    QColor getDefaultTextColor() const;
    void setWeekendsTextColor(const QColor & color);
    QColor getWeekendsTextColor() const;
    void setSelectedTextColor(const QColor & color);
    QColor getSelectedTextColor() const;
    void setFestivalTextColor(const QColor & color);
    QColor getFestivalTextColor() const;
    void setDefaultLunarColor(const QColor & color);
    QColor getDefaultLunarColor() const;
    void setWeekendsLunarColor(const QColor & color);
    QColor getWeekendsLunarColor() const;
    void setSelectedLunarColor(const QColor & color);
    QColor getSelectedLunarColor() const;
    void setFestivalLunarColor(const QColor & color);
    QColor getFestivalLunarColor() const;

signals:
    void selectedDateChanged(const QDate & date);

public slots:
    inline void resetDate() {setDate(currentDate);}
    inline void setDate(const QDate & date) {usingDate = selectDate = date; adjustDate();}
    void adjustDate();
    void maybeChangeMonth(const QModelIndex & clickedIndex);
    void selectedIndexChanged(const QModelIndex & index);

private:
    void resizeEvent(QResizeEvent *e);

private:
    DUI::DImageButton prevYear;
    DUI::DImageButton nextYear;
    DUI::DImageButton prevMonth;
    DUI::DImageButton nextMonth;
    DUI::DTextButton m_resetBtn;

    QLineEdit year;
    QLineEdit month;

    QLabel datailOfToday;

    QDate usingDate;
    QDate selectDate;
    QDate currentDate;

    int outerWidth;
    int outerHeight;

    bool m_lunarVisible = true;

    DCalendarView *cViewLeft;
    DCalendarView *cViewRight;
    DCalendarView *cViewCurrent;
    DCalendarDelegate *cDelegate;
    DCalendarModel *currentModel;
    DCalendarModel *nextStepModel;

    QWidget *outerWidget;
    QWidget *innerWidget;

    QPropertyAnimation *m_animation;
};

DUI_END_NAMESPACE

#endif // DCALENDAR_H
