#include "dheaderline.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DHeaderLine::DHeaderLine(QWidget *parent) : DBaseLine(parent)
{
    D_THEME_INIT_WIDGET(DHeaderLine);

    setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    setFixedHeight(DUI::EXPAND_HEADER_HEIGHT);
    m_titleLabel = new QLabel(this);
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
    setFixedHeight(DUI::CONTENT_HEADER_HEIGHT);
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
