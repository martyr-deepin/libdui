#include <QDebug>

#include "dthememanager.h"

#include "dwindowclosebutton.h"

DUI_BEGIN_NAMESPACE

DWindowCloseButton::DWindowCloseButton(QWidget * parent) :
    DImageButton(parent)
{
    D_THEME_INIT_WIDGET(DWindowCloseButton);
}

QString DWindowCloseButton::normalImage() const
{
    return m_normalImage;
}

void DWindowCloseButton::setNormalImage(const QString &normalImage)
{
    m_normalImage = normalImage;

    this->setNormalPic(m_normalImage);
}

QString DWindowCloseButton::hoverImage() const
{
    return m_hoverImage;
}

void DWindowCloseButton::setHoverImage(const QString &hoverImage)
{
    m_hoverImage = hoverImage;

    this->setHoverPic(m_hoverImage);
}

QString DWindowCloseButton::pressedImage() const
{
    return m_pressedImage;
}

void DWindowCloseButton::setPressedImage(const QString &pressedImage)
{
    m_pressedImage = pressedImage;

    this->setPressPic(m_pressedImage);
}

DUI_END_NAMESPACE


