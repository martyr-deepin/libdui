#include <QDebug>
#include <QFile>
#include <QStyle>

#include "dthememanager.h"

#include "dwindowminbutton.h"

DUI_BEGIN_NAMESPACE

DWindowMinButton::DWindowMinButton(QWidget * parent) :
    DImageButton(parent)
{
    D_THEME_INIT_WIDGET(DWindowMinButton);
}

QString DWindowMinButton::normalImage() const
{
    return m_normalImage;
}

void DWindowMinButton::setNormalImage(const QString &normalImage)
{
    m_normalImage = normalImage;

    this->setNormalPic(m_normalImage);
}

QString DWindowMinButton::hoverImage() const
{
    return m_hoverImage;
}

void DWindowMinButton::setHoverImage(const QString &hoverImage)
{
    m_hoverImage = hoverImage;

    this->setHoverPic(m_hoverImage);
}

QString DWindowMinButton::pressedImage() const
{
    return m_pressedImage;
}

void DWindowMinButton::setPressedImage(const QString &pressedImage)
{
    m_pressedImage = pressedImage;

    this->setPressPic(m_pressedImage);
}

DUI_END_NAMESPACE
