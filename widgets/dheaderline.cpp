#include "dheaderline.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DHeaderLine::DHeaderLine(QWidget *parent) : DBaseLine(parent)
{
    D_THEME_INIT_WIDGET(DHeaderLine);

    m_titleLabel = new QLabel(this);
    setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_titleLabel->setObjectName("DHeaderLineTitle");
    setLeftContent(m_titleLabel);
}

void DHeaderLine::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
}

void DHeaderLine::setContent(QWidget *content)
{
    setRightContent(content);
}

void DHeaderLine::setLeftContent(QWidget *content)
{
    DBaseLine::setLeftContent(content);
}

void DHeaderLine::setRightContent(QWidget *content)
{
    DBaseLine::setRightContent(content);
}

DUI_END_NAMESPACE
