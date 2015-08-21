#include <QDebug>

#include "dthememanager.h"

#include "dwindowoptionbutton.h"

DUI_BEGIN_NAMESPACE

DWindowOptionButton::DWindowOptionButton(QWidget * parent) :
    DImageButton(parent)
{
    D_THEME_INIT_WIDGET(DWindowOptionButton);
}

QString DWindowOptionButton::normalImage() const
{
    return m_normalImage;
}

void DWindowOptionButton::setNormalImage(const QString &normalImage)
{
    m_normalImage = normalImage;

    this->setNormalPic(m_normalImage);
}

QString DWindowOptionButton::hoverImage() const
{
    return m_hoverImage;
}

void DWindowOptionButton::setHoverImage(const QString &hoverImage)
{
    m_hoverImage = hoverImage;

    this->setHoverPic(m_hoverImage);
}

QString DWindowOptionButton::pressedImage() const
{
    return m_pressedImage;
}

void DWindowOptionButton::setPressedImage(const QString &pressedImage)
{
    m_pressedImage = pressedImage;

    this->setPressPic(m_pressedImage);
}

DUI_END_NAMESPACE


