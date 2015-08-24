#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QEvent>

#include "dscrollarea.h"
#include "dthememanager.h"
#include "dscrollbar.h"

DUI_BEGIN_NAMESPACE

DScrollArea::DScrollArea(QWidget *parent) :
    QScrollArea(parent),
    m_autoHideScrollBar(false),
    m_vBar(new DScrollBar),
    m_hBar(new DScrollBar),
    m_scrollBarAnimation(0),
    m_timer(0)
{
    this->setVerticalScrollBar(m_vBar);
    this->setHorizontalScrollBar(m_hBar);

    connect(m_vBar, &DScrollBar::valueChanged, [&]{
        showScrollBar(m_vBar);
    });
    connect(m_hBar, &DScrollBar::valueChanged, [&]{
        showScrollBar(m_hBar);
    });

    D_THEME_INIT_WIDGET(DScrollArea);
}

bool DScrollArea::autoHideScrollBar() const
{
    return m_autoHideScrollBar;
}

void DScrollArea::setAutoHideScrollBar(bool autoHideScrollBar)
{
    if (m_autoHideScrollBar == autoHideScrollBar)
        return;

    m_autoHideScrollBar = autoHideScrollBar;

    if(autoHideScrollBar){
        if(!m_scrollBarAnimation)
            m_scrollBarAnimation = new QPropertyAnimation(this, "windowOpacity");
        if(!m_timer)
            m_timer = new QTimer(this);

        m_scrollBarAnimation->setDuration(300);
        m_timer->setSingleShot(true);

        m_vBar->hide();
        m_hBar->hide();

        connect(m_timer, &QTimer::timeout, [&]{
            if(m_vBar->isVisible())
                hideScrollBar(m_vBar);
            if(m_hBar->isVisible())
                hideScrollBar(m_hBar);
        });
    }else{
        if(m_scrollBarAnimation)
            m_scrollBarAnimation->deleteLater();
        if(m_timer)
            m_timer->deleteLater();

        showScrollBar(m_vBar);
        showScrollBar(m_hBar);
    }

    emit autoHideScrollBarChanged(autoHideScrollBar);
}

void DScrollArea::hideScrollBar(QScrollBar *bar)
{
    if(bar->isHidden())
        return;

    if(m_scrollBarAnimation){
        connect(m_scrollBarAnimation, &QPropertyAnimation::finished, bar, &DScrollBar::hide);
        connect(m_scrollBarAnimation, &QPropertyAnimation::finished, bar, &DScrollBar::hide);

        m_scrollBarAnimation->setStartValue(1.0);
        m_scrollBarAnimation->setEndValue(0.0);
        m_scrollBarAnimation->start();
    }else{
        bar->hide();
    }
}

void DScrollArea::showScrollBar(QScrollBar *bar)
{
    if(bar->isVisible())
        return;

    if(bar == m_vBar && verticalScrollBarPolicy() != Qt::ScrollBarAlwaysOff)
        m_vBar->show();
    else if(bar == m_hBar && horizontalScrollBarPolicy() != Qt::ScrollBarAlwaysOff)
        m_hBar->show();

    if(m_scrollBarAnimation){
        disconnect(m_scrollBarAnimation, &QPropertyAnimation::finished, bar, &DScrollBar::hide);
        disconnect(m_scrollBarAnimation, &QPropertyAnimation::finished, bar, &DScrollBar::hide);

        m_scrollBarAnimation->setStartValue(1.0);
        m_scrollBarAnimation->setEndValue(0.0);
        m_scrollBarAnimation->start();
        m_timer->start(1000);
    }
}

DUI_END_NAMESPACE
