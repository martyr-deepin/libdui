#ifndef DWINDOWMINBUTTON_H
#define DWINDOWMINBUTTON_H

#include "dimagebutton.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DWindowMinButton : public DImageButton
{
    Q_OBJECT
public:
    DWindowMinButton(QWidget * parent = 0);

    Q_PROPERTY(QString normalImage READ normalImage WRITE setNormalImage)
    Q_PROPERTY(QString hoverImage READ hoverImage WRITE setHoverImage)
    Q_PROPERTY(QString pressedImage READ pressedImage WRITE setPressedImage)

    QString normalImage() const;
    void setNormalImage(const QString &normalImage);

    QString hoverImage() const;
    void setHoverImage(const QString &hoverImage);

    QString pressedImage() const;
    void setPressedImage(const QString &pressedImage);

private:
    QString m_normalImage;
    QString m_hoverImage;
    QString m_pressedImage;
};

DUI_END_NAMESPACE

#endif // DWINDOWMINBUTTON_H
