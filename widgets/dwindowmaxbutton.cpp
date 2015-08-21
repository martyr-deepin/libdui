#include <QDebug>

#include "dthememanager.h"

#include "dwindowmaxbutton.h"

DUI_BEGIN_NAMESPACE

DWindowMaxButton::DWindowMaxButton(QWidget * parent) :
    DImageButton(parent)
{
    D_THEME_INIT_WIDGET(DWindowMaxButton);
}

QString DWindowMaxButton::normalImage() const
{
    return m_normalImage;
}

void DWindowMaxButton::setNormalImage(const QString &normalImage)
{
    m_normalImage = normalImage;

    this->setNormalPic(m_normalImage);
}

QString DWindowMaxButton::hoverImage() const
{
    return m_hoverImage;
}

void DWindowMaxButton::setHoverImage(const QString &hoverImage)
{
    m_hoverImage = hoverImage;

    this->setHoverPic(m_hoverImage);
}

QString DWindowMaxButton::pressedImage() const
{
    return m_pressedImage;
}

void DWindowMaxButton::setPressedImage(const QString &pressedImage)
{
    m_pressedImage = pressedImage;

    this->setPressPic(m_pressedImage);
}

DUI_END_NAMESPACE


