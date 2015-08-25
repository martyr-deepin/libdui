#include "dbaseexpand.h"
#include "dthememanager.h"

#include <QResizeEvent>

DUI_BEGIN_NAMESPACE

DBaseExpand::DBaseExpand(QWidget *parent) : QWidget(parent)
{
    D_THEME_INIT_WIDGET(DBaseExpand);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_headerLayout = new QVBoxLayout();
    m_headerLayout->setContentsMargins(0, 0, 0, 0);
    m_headerLayout->setAlignment(Qt::AlignCenter);

    m_hSeparator = new DSeparatorHorizontal();

    m_contentLayout = new QVBoxLayout();
    m_contentLayout->setAlignment(Qt::AlignCenter);
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentLoader = new ContentLoader();
    m_contentLoader->setFixedHeight(0); // default to not expanded.
    m_contentLoader->setLayout(m_contentLayout);

    m_animation = new QPropertyAnimation(m_contentLoader, "height");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InSine);
    connect(m_animation, &QPropertyAnimation::valueChanged, this, &DBaseExpand::adjustSize);

    mainLayout->addLayout(m_headerLayout);
    mainLayout->addWidget(m_hSeparator);
    mainLayout->addWidget(m_contentLoader);

    setLayout(mainLayout);

    updateContentHeight();
}

void DBaseExpand::setHeader(QWidget *header)
{
    if (!header)
        return;

    QLayoutItem *child;
    while ((child = m_headerLayout->takeAt(0)) != 0) {
        m_headerLayout->removeItem(child);
    }

    m_headerLayout->addWidget(header);
    m_header = header;
}

void DBaseExpand::setContent(QWidget *content)
{
    if (!content)
        return;

    QLayoutItem *child;
    while ((child = m_contentLayout->takeAt(0)) != 0) {
        m_contentLayout->removeItem(child);
    }

    m_contentLayout->addWidget(content);
    m_contentLayout->addStretch(1);
    m_content = content;

    updateContentHeight();
}

void DBaseExpand::setHeaderHeight(int height)
{
    if (m_header)
        m_header->setFixedHeight(height);
}

void DBaseExpand::setExpand(bool value)
{
    m_expand = value;

    if (!m_content)
        return;

    emit expandChange(value);

    if (value)
    {
        m_animation->setStartValue(m_contentLoader->height());
        m_animation->setEndValue(m_content->height());
    }
    else
    {
        m_animation->setStartValue(m_contentLoader->height());
        m_animation->setEndValue(0);
    }

    m_animation->stop();
    m_animation->start();
}

void DBaseExpand::updateContentHeight()
{
    int endHeight = 0;
    if (m_content){
        if (m_expand)
            endHeight = m_content->height();
    }

    m_animation->setStartValue(m_contentLoader->height());
    m_animation->setEndValue(endHeight);
    m_animation->stop();
    m_animation->start();
}

bool DBaseExpand::expand() const
{
    return m_expand;
}

void DBaseExpand::setAnimationDuration(int duration)
{
    m_animation->setDuration(duration);
}

void DBaseExpand::setAnimationEasingCurve(QEasingCurve curve)
{
    m_animation->setEasingCurve(curve);
}


DUI_END_NAMESPACE
