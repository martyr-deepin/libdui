#ifndef DWINDOWOPTIONBUTTON_H
#define DWINDOWOPTIONBUTTON_H

#include <QObject>
#include <QString>

#include "dimagebutton.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DWindowOptionButton : public DImageButton
{
    Q_OBJECT
public:
    DWindowOptionButton(QWidget * parent = 0);

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

#endif // DWINDOWOPTIONBUTTON_H
