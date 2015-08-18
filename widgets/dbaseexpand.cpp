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
    m_headerLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_hSeparator = new DSeparatorHorizontal(this);
    m_contentLayout = new QVBoxLayout();
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_contentLoader = new ContentLoader(this);
    m_contentLoader->setLayout(m_contentLayout);

    m_animation = new QPropertyAnimation(m_contentLoader, "height");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InSine);
    connect(m_animation, &QPropertyAnimation::valueChanged, this, &DBaseExpand::adjustSize);

    mainLayout->addLayout(m_headerLayout);
    mainLayout->addWidget(m_hSeparator);
    mainLayout->addWidget(m_contentLoader);

    setLayout(mainLayout);
}

void DBaseExpand::setHeader(QWidget *header)
{
    if (!header)
        return;

    QLayoutItem *child;
    while ((child = m_headerLayout->takeAt(0)) != 0) {
        m_headerLayout->removeItem(child);
    }

    m_hSeparator->setFixedWidth(width());
    header->setFixedSize(width(), m_headerHeight);
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

    m_contentLoader->setFixedSize(width(), expand() ? content->height() : 0);
    m_contentLayout->addWidget(content);
    m_contentLayout->addStretch(1);
    m_content = content;
}

void DBaseExpand::setHeaderHeight(int height)
{
    if (m_header)
        m_header->setFixedHeight(height);

    m_headerHeight = height;    //for height change before header set
}

void DBaseExpand::setExpand(bool value)
{
    m_expand = value;

    if (!m_content)
        return;

    emit expandChange(value);

    if (value)
    {
        m_animation->setStartValue(0);
        m_animation->setEndValue(m_content->height());
    }
    else
    {
        m_animation->setStartValue(m_content->height());
        m_animation->setEndValue(0);
    }

    m_animation->stop();
    m_animation->start();
}

void DBaseExpand::updateContentHeight()
{
    if (!m_content)
        return;

    m_animation->setStartValue(m_contentLoader->height());
    m_animation->setEndValue(m_content->height());
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

void DBaseExpand::resizeEvent(QResizeEvent *e)
{
    m_hSeparator->setFixedWidth(e->size().width());
    m_contentLoader->setFixedWidth(e->size().width());
    if (m_content)
        m_content->setFixedWidth(e->size().width());
    if (m_header)
        m_header->setFixedSize(e->size().width(), m_headerHeight);

    QWidget::resizeEvent(e);

    emit sizeChanged(size());
}

DUI_END_NAMESPACE
