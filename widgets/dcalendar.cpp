#include "dcalendar.h"
#include "dimagebutton.h"
#include "dthememanager.h"
#include "private/DCalendarWidget/calendarview.h"

#include <QHBoxLayout>
#include <QResizeEvent>
#include <QDebug>

DUI_BEGIN_NAMESPACE

DCalendar::DCalendar(QWidget *parent) : QWidget(parent)
{
    D_THEME_INIT_WIDGET(DCalendar);

    m_detailLabel = new QLabel;
#ifdef QT_DEBUG
    m_detailLabel->setText("detail label");
#endif
    m_yearEdt = new QLineEdit;
    m_yearEdt->setEnabled(false);
    m_yearEdt->setFixedWidth(40);
    m_yearEdt->setAlignment(Qt::AlignCenter);
    m_monEdt = new QLineEdit;
    m_monEdt->setEnabled(false);
    m_monEdt->setFixedWidth(25);
    m_monEdt->setAlignment(Qt::AlignCenter);
    m_resetBtn = new DLinkButton;
    m_resetBtn->setText(tr("Reset"));
    m_resetBtn->hide();
    m_viewLeft = new CalendarView;
    m_viewLeft->setObjectName("CalendarView");
    m_viewCurrent = m_viewLeft;
    m_viewRight = new CalendarView;
    m_viewRight->setCurrentDate(QDate::currentDate());
    m_viewRight->setObjectName("CalendarView");
    m_viewOuterWidget = new QWidget;
    m_viewOuterWidget->installEventFilter(this);
    m_viewOuterWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_viewInnerWidget = new QWidget(m_viewOuterWidget);
    m_currentDate = QDate::currentDate();
    m_showDate = m_currentDate;
    m_animation = new QPropertyAnimation(m_viewInnerWidget, "geometry");

    DImageButton *prevYear = new DImageButton;
    prevYear->setNormalPic(":/images/arrow_left_normal.png");
    prevYear->setHoverPic(":/images/arrow_left_hover.png");
    prevYear->setPressPic(":/images/arrow_left_press.png");
    DImageButton *nextYear = new DImageButton;
    nextYear->setNormalPic(":/images/arrow_right_normal.png");
    nextYear->setHoverPic(":/images/arrow_right_hover.png");
    nextYear->setPressPic(":/images/arrow_right_press.png");
    DImageButton *prevMon = new DImageButton;
    prevMon->setNormalPic(":/images/arrow_left_normal.png");
    prevMon->setHoverPic(":/images/arrow_left_hover.png");
    prevMon->setPressPic(":/images/arrow_left_press.png");
    DImageButton *nextMon = new DImageButton;
    nextMon->setNormalPic(":/images/arrow_right_normal.png");
    nextMon->setHoverPic(":/images/arrow_right_hover.png");
    nextMon->setPressPic(":/images/arrow_right_press.png");

    QHBoxLayout *topCtrlLayout = new QHBoxLayout;
    topCtrlLayout->addWidget(prevYear);
    topCtrlLayout->addWidget(m_yearEdt);
    topCtrlLayout->addWidget(nextYear);
    topCtrlLayout->addWidget(prevMon);
    topCtrlLayout->addWidget(m_monEdt);
    topCtrlLayout->addWidget(nextMon);
    topCtrlLayout->addStretch();
    topCtrlLayout->addWidget(m_resetBtn);
    topCtrlLayout->setMargin(0);
    topCtrlLayout->setSpacing(0);

    QHBoxLayout *viewsLayout = new QHBoxLayout;
    viewsLayout->addWidget(m_viewLeft);
    viewsLayout->addWidget(m_viewRight);
    viewsLayout->setMargin(0);
    viewsLayout->setSpacing(0);

    m_viewInnerWidget->setLayout(viewsLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topCtrlLayout);
    mainLayout->addWidget(m_detailLabel);
    mainLayout->addWidget(m_viewOuterWidget);

    connect(m_viewLeft, &CalendarView::dateSelected, this, &DCalendar::viewDateChanged);
    connect(m_viewRight, &CalendarView::dateSelected, this, &DCalendar::viewDateChanged);
    connect(m_resetBtn, &DLinkButton::clicked, [this] {selectDate(m_currentDate);});
    connect(prevYear, &DImageButton::clicked, [this] {selectDate(m_showDate.addYears(-1));});
    connect(prevMon, &DImageButton::clicked, [this] {selectDate(m_showDate.addMonths(-1));});
    connect(nextYear, &DImageButton::clicked, [this] {selectDate(m_showDate.addYears(1));});
    connect(nextMon, &DImageButton::clicked, [this] {selectDate(m_showDate.addMonths(1));});

    setCurrentDate(m_currentDate);
    setLayout(mainLayout);
}

DCalendar::~DCalendar()
{
    m_animation->deleteLater();
}

void DCalendar::setCurrentDate(const QDate &date)
{
    selectDate(date);

    m_currentDate = date;
    m_showDate = date;
}

void DCalendar::selectDate(const QDate &date)
{
    qDebug() << m_showDate << date;
    const QDate oldDate = m_showDate;
    m_showDate = date;

    if (date.year() < oldDate.year())
        aniToPrev();
    else if (date.year() > oldDate.year())
        aniToNext();
    else if (date.month() < oldDate.month())
        aniToPrev();
    else if (date.month() > oldDate.month())
        aniToNext();

    if (date == m_currentDate)
        m_resetBtn->hide();
    else
        m_resetBtn->show();

    m_monEdt->setText(QString::number(date.month()));
    m_yearEdt->setText(QString::number(date.year()));
    m_viewCurrent->setCurrentDate(m_showDate);

    emit selectedDateChanged(date);
}

void DCalendar::setLunarVisible(bool visible)
{
    m_viewLeft->setLunarVisible(visible);
    m_viewRight->setLunarVisible(visible);
    m_detailLabel->setVisible(visible);
}

void DCalendar::setLunarFestivalHighlight(bool highlight)
{
    m_viewLeft->setLunarFestivalHighlight(highlight);
    m_viewRight->setLunarFestivalHighlight(highlight);
}

bool DCalendar::eventFilter(QObject *o, QEvent *e)
{
    // update inner widget geometery
    if (o == m_viewOuterWidget && e->type() == QEvent::Resize)
    {
        m_viewSize = m_viewOuterWidget->size();

        if (m_viewCurrent == m_viewLeft)
            m_viewInnerWidget->setGeometry(0, 0, m_viewSize.width() * 2, m_viewSize.height());
        else
            m_viewInnerWidget->setGeometry(m_viewSize.width(), 0, m_viewSize.width() * 2, m_viewSize.height());
    }

    return false;
}

void DCalendar::viewDateChanged(const QDate &date, const QString &detail)
{
    qDebug() << date << detail;
    if (sender() != m_viewCurrent)
        return;

    selectDate(date);
    m_detailLabel->setText(detail);
}

void DCalendar::aniToPrev()
{
    m_animation->stop();
    m_animation->setStartValue(QRect(-m_viewSize.width(), 0, m_viewSize.width() * 2, m_viewSize.height()));
    m_animation->setEndValue(QRect(0, 0, m_viewSize.width() * 2, m_viewSize.height()));
    m_animation->start();

    m_viewCurrent = m_viewLeft;
}

void DCalendar::aniToNext()
{
    m_animation->stop();
    m_animation->setStartValue(QRect(0, 0, m_viewSize.width() * 2, m_viewSize.height()));
    m_animation->setEndValue(QRect(-m_viewSize.width(), 0, m_viewSize.width() * 2, m_viewSize.height()));
    m_animation->start();

    m_viewCurrent = m_viewRight;
}

DUI_END_NAMESPACE
