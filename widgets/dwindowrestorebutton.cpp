#include <QDebug>

#include "dthememanager.h"

#include "dwindowrestorebutton.h"

DUI_BEGIN_NAMESPACE

DWindowRestoreButton::DWindowRestoreButton(QWidget * parent) :
    DImageButton(parent)
{
    D_THEME_INIT_WIDGET(DWindowRestoreButton);
}

QString DWindowRestoreButton::normalImage() const
{
    return m_normalImage;
}

void DWindowRestoreButton::setNormalImage(const QString &normalImage)
{
    m_normalImage = normalImage;

    this->setNormalPic(m_normalImage);
}

QString DWindowRestoreButton::hoverImage() const
{
    return m_hoverImage;
}

void DWindowRestoreButton::setHoverImage(const QString &hoverImage)
{
    m_hoverImage = hoverImage;

    this->setHoverPic(m_hoverImage);
}

QString DWindowRestoreButton::pressedImage() const
{
    return m_pressedImage;
}

void DWindowRestoreButton::setPressedImage(const QString &pressedImage)
{
    m_pressedImage = pressedImage;

    this->setPressPic(m_pressedImage);
}

DUI_END_NAMESPACE


