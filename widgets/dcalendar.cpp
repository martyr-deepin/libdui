#include "dcalendar.h"
#include "dthememanager.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QSpacerItem>
#include <QVBoxLayout>

#include "private/DCalendar/dcalendarview.h"
#include "private/DCalendar/dcalendardelegate.h"
#include "private/DCalendar/dcalendarmodel.h"

DUI_BEGIN_NAMESPACE

DCalendar::DCalendar(QWidget *parent) : QWidget(parent),
    m_resetBtn(tr("Reset")),
    usingDate(QDate::currentDate()),
    selectDate(QDate::currentDate()),
    currentDate(QDate::currentDate())
{
    D_THEME_INIT_WIDGET(DCalendar);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    cViewCurrent = cViewLeft = new DCalendarView(this);
    cViewRight = new DCalendarView(this);
    cDelegate = new DCalendarDelegate(this);
    currentModel = new DCalendarModel();
    nextStepModel = new DCalendarModel();
    cViewLeft->setItemDelegate(cDelegate);
    cViewLeft->setModel(nextStepModel);
    cViewRight->setItemDelegate(cDelegate);
    cViewRight->setModel(nextStepModel);

    QSpacerItem *hSpace = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout *dateItems = new QHBoxLayout;
    dateItems->addWidget(&prevYear);
    dateItems->addWidget(&year);
    dateItems->addWidget(&nextYear);
    dateItems->addWidget(&prevMonth);
    dateItems->addWidget(&month);
    dateItems->addWidget(&nextMonth);
    dateItems->addItem(hSpace);
    dateItems->addWidget(&m_resetBtn);

    QHBoxLayout *viewsLayout = new QHBoxLayout;
    viewsLayout->addWidget(cViewLeft);
    viewsLayout->addWidget(cViewRight);
    viewsLayout->setMargin(0);
    viewsLayout->setSpacing(0);

    outerWidget = new QWidget;
    outerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    innerWidget = new QWidget(outerWidget);
    innerWidget->setLayout(viewsLayout);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addItem(dateItems);
    centralLayout->addWidget(&datailOfToday);
    centralLayout->addWidget(outerWidget);

    setLayout(centralLayout);

#ifdef QT_DEBUG
    datailOfToday.setText("details");
#endif
    prevYear.setText("<");
    nextYear.setText(">");
    prevMonth.setText("<");
    nextMonth.setText(">");
    year.setText(QString::number(usingDate.year()));
    month.setText(QString::number(usingDate.month()));

    year.setFixedWidth(40);
    month.setFixedWidth(20);

    m_resetBtn.hide();

    const int btnWidth = 20;
    prevYear.setMaximumWidth(btnWidth);
    nextYear.setMaximumWidth(btnWidth);
    prevMonth.setMaximumWidth(btnWidth);
    nextMonth.setMaximumWidth(btnWidth);

    connect(&prevYear, &QPushButton::clicked, [this] () -> void {selectDate = selectDate.addYears(-1); adjustDate();});
    connect(&nextYear, &QPushButton::clicked, [this] () -> void {selectDate = selectDate.addYears(1); adjustDate();});
    connect(&prevMonth, &QPushButton::clicked, [this] () -> void {selectDate = selectDate.addMonths(-1); adjustDate();});
    connect(&nextMonth, &QPushButton::clicked, [this] () -> void {selectDate = selectDate.addMonths(1); adjustDate();});
    connect(&m_resetBtn, &QPushButton::clicked, this, &DCalendar::resetDate);

    connect(cViewLeft, SIGNAL(cellClicked(QModelIndex)), this, SLOT(maybeChangeMonth(QModelIndex)), Qt::QueuedConnection);
    connect(cViewRight, SIGNAL(cellClicked(QModelIndex)), this, SLOT(maybeChangeMonth(QModelIndex)), Qt::QueuedConnection);

    connect(currentModel, SIGNAL(selectedCellChanged(QModelIndex)), this, SLOT(selectedIndexChanged(QModelIndex)), Qt::QueuedConnection);
    connect(nextStepModel, SIGNAL(selectedCellChanged(QModelIndex)), this, SLOT(selectedIndexChanged(QModelIndex)), Qt::QueuedConnection);

    nextStepModel->setDate(QDate::currentDate());
    currentModel->setDate(QDate::currentDate());

    outerHeight = outerWidget->height();
    outerWidth = outerWidget->width();
    innerWidget->setGeometry(0, 0, outerWidth * 2, outerHeight);

    cViewLeft->setObjectName("DCalendarView");
    cViewRight->setObjectName("DCalendarView");
}

inline QDate DCalendar::getCurrentDate() const
{
    return usingDate;
}

inline QDate DCalendar::getSelectDate() const
{
    return selectDate;
}

void DCalendar::animationToPrev()
{
    qDebug() << "prev";
    cViewLeft->setModel(nextStepModel);
    cViewRight->setModel(currentModel);
    QPropertyAnimation *animation = new QPropertyAnimation(innerWidget, "geometry");
    animation->setDuration(animationDuration);
    animation->setStartValue(QRect(-outerWidth, 0, outerWidth * 2, outerHeight));
    animation->setEndValue(QRect(0, 0, outerWidth * 2, outerHeight));
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start();

    cViewCurrent = cViewLeft;
}

void DCalendar::animationToNext()
{
    qDebug() << "next";
    cViewLeft->setModel(currentModel);
    cViewRight->setModel(nextStepModel);
    QPropertyAnimation *animation = new QPropertyAnimation(innerWidget, "geometry");
    animation->setDuration(animationDuration);
    animation->setStartValue(QRect(0, 0, outerWidth * 2, outerHeight));
    animation->setEndValue(QRect(-outerWidth, 0, outerWidth * 2, outerHeight));
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start();

    cViewCurrent = cViewRight;
}

void DCalendar::adjustDate()
{
    year.setText(QString::number(selectDate.year()));
    month.setText(QString::number(selectDate.month()));

    nextStepModel->setDate(selectDate);
    currentModel->setDate(usingDate);

    if (selectDate.year() < usingDate.year())
        animationToPrev();
    else if (selectDate.year() > usingDate.year())
        animationToNext();
    else if (selectDate.month() < usingDate.month())
        animationToPrev();
    else if (selectDate.month() > usingDate.month())
        animationToNext();

    usingDate = selectDate;

    if (selectDate == currentDate)
        m_resetBtn.hide();
    else
        m_resetBtn.show();

    emit selectedDateChanged(selectDate);
}

void DCalendar::maybeChangeMonth(const QModelIndex &clickedIndex)
{
    DCalendarModel *model = (DCalendarModel *)(clickedIndex.model());
    if (!model || model != cViewCurrent->model())
        return;

    int dayNum = model->getDayNum(clickedIndex);

    if (clickedIndex.row() == 0 && dayNum >= 23)
        selectDate = selectDate.addMonths(-1);
    if (clickedIndex.row() > 3 && dayNum <= 14)
        selectDate = selectDate.addMonths(1);

    selectDate = QDate(selectDate.year(), selectDate.month(), dayNum);

    adjustDate();
}

void DCalendar::selectedIndexChanged(const QModelIndex &index)
{
    //cViewLeft->setCurrentIndex(index);
    //cViewRight->setCurrentIndex(index);
    if (!index.isValid())
        return;

    if (cViewCurrent && cViewCurrent->model() == index.model())
        cViewCurrent->setCurrentIndex(index);
}

void DCalendar::resizeEvent(QResizeEvent *e)
{
    outerWidth = outerWidget->width();
    outerHeight = outerWidget->height();

    innerWidget->setGeometry(0, 0, outerWidth * 2, outerHeight);

    return QWidget::resizeEvent(e);
}

void DCalendar::setBackgroundColor(const QColor &color)
{
    cDelegate->setBackgroundColor(color);
}

QColor DCalendar::getBackgroundColor() const
{
    return cDelegate->getBackgroundColor();
}

void DCalendar::setBackgroundCircleColor(const QColor &color)
{
    cDelegate->setBackgroundCircleColor(color);
}

QColor DCalendar::getBackgroundCircleColor() const
{
    return cDelegate->getBackgroundCircleColor();
}

void DCalendar::setDefaultTextColor(const QColor &color)
{
    cDelegate->setDefaultTextColor(color);
}

QColor DCalendar::getDefaultTextColor() const
{
    return cDelegate->getDefaultTextColor();
}

void DCalendar::setWeekendsTextColor(const QColor &color)
{
    cDelegate->setWeekendsTextColor(color);
}

QColor DCalendar::getWeekendsTextColor() const
{
    return cDelegate->getWeekendsTextColor();
}

void DCalendar::setSelectedTextColor(const QColor &color)
{
    cDelegate->setSelectedTextColor(color);
}

QColor DCalendar::getSelectedTextColor() const
{
    return cDelegate->getSelectedTextColor();
}

void DCalendar::setFestivalTextColor(const QColor &color)
{
    cDelegate->setFestivalTextColor(color);
}

QColor DCalendar::getFestivalTextColor() const
{
    return cDelegate->getFestivalTextColor();
}

void DCalendar::setDefaultLunarColor(const QColor &color)
{
    cDelegate->setDefaultLunarColor(color);
}

QColor DCalendar::getDefaultLunarColor() const
{
    return cDelegate->getDefaultLunarColor();
}

void DCalendar::setWeekendsLunarColor(const QColor &color)
{
    cDelegate->setWeekendsLunarColor(color);
}

QColor DCalendar::getWeekendsLunarColor() const
{
    return cDelegate->getWeekendsLunarColor();
}

void DCalendar::setSelectedLunarColor(const QColor &color)
{
    cDelegate->setSelectedLunarColor(color);
}

QColor DCalendar::getSelectedLunarColor() const
{
    return cDelegate->getSelectedLunarColor();
}

void DCalendar::setFestivalLunarColor(const QColor &color)
{
    cDelegate->setFestivalLunarColor(color);
}

QColor DCalendar::getFestivalLunarColor() const
{
    return cDelegate->getFestivalLunarColor();
}

DUI_END_NAMESPACE

