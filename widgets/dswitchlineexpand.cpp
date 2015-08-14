#include "dswitchlineexpand.h"
#include "dthememanager.h"

#include <QResizeEvent>

DUI_BEGIN_NAMESPACE

SwitchHeaderLine::SwitchHeaderLine(QWidget *parent) :
    DHeaderLine(parent)
{
    m_switchButton = new DSwitchButton(this);
    connect(m_switchButton, &DSwitchButton::checkedChanged, this, &SwitchHeaderLine::mousePress);
    setContent(m_switchButton);
}

void SwitchHeaderLine::setExpand(bool value)
{
    m_switchButton->setChecked(value);
}

void SwitchHeaderLine::mousePressEvent(QMouseEvent *)
{
    emit mousePress();
}

DSwitchLineExpand::DSwitchLineExpand(QWidget *parent) :
    DBaseExpand(parent)
{
    m_headerLine = new SwitchHeaderLine(this);
    m_headerLine->setExpand(expand());
    connect(m_headerLine, &SwitchHeaderLine::mousePress, [=]{
        setExpand(!expand());
    });
    setHeader(m_headerLine);
}

void DSwitchLineExpand::setTitle(const QString &title)
{
    m_headerLine->setTitle(title);
}

void DSwitchLineExpand::setExpand(bool value)
{
    //Header's arrow direction change here
    m_headerLine->setExpand(value);
    DBaseExpand::setExpand(value);
}

void DSwitchLineExpand::setHeader(QWidget *header)
{
    DBaseExpand::setHeader(header);
}

void DSwitchLineExpand::resizeEvent(QResizeEvent *e)
{
    m_headerLine->setFixedWidth(e->size().width());

    DBaseExpand::resizeEvent(e);
}

DUI_END_NAMESPACE
