#include "dsearchedit.h"

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPropertyAnimation>
#include <QDebug>

DUI_BEGIN_NAMESPACE

DSearchEdit::DSearchEdit(QWidget *parent)
    : QWidget(parent),
      m_btn(this)
{
    D_THEME_INIT_WIDGET(DSearchEdit);

    m_size = QSize(m_btn.sizeHint().width() + m_edt.sizeHint().width(), qMax(m_btn.sizeHint().height(), m_edt.sizeHint().height()));
    setFixedSize(m_size);
    m_edt.setFixedWidth(0);

    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addSpacerItem(spacer);
    layout->addWidget(&m_btn);
    layout->addWidget(&m_edt);
    layout->addSpacerItem(spacer);
    layout->setSpacing(0);
    layout->setMargin(0);

    setLayout(layout);
}

void DSearchEdit::enterEvent(QEvent *)
{
    //m_edt.setFixedWidth(m_size.width() - m_btn.width());

    QPropertyAnimation *animation = new QPropertyAnimation(&m_edt, "maximumWidth");
    animation->setStartValue(0);
    animation->setEndValue(m_size.width() - m_btn.width());
    animation->setDuration(animationDuration);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start();

    m_edt.setFocus();
}

void DSearchEdit::leaveEvent(QEvent *)
{
    //m_edt.setFixedWidth(0);

    QPropertyAnimation *animation = new QPropertyAnimation(&m_edt, "maximumWidth");
    animation->setEndValue(0);
    animation->setStartValue(m_edt.width());
    animation->setDuration(animationDuration);
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->start();
}

DUI_END_NAMESPACE

