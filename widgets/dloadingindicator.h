#ifndef DLOADINGINDICATOR_H
#define DLOADINGINDICATOR_H

#include <QObject>
#include <QBrush>
#include <QColor>
#include <QVariant>
#include <QSizePolicy>
#include <QVariantAnimation>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QEasingCurve>
#include <QDebug>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DLoadingIndicator : public QGraphicsView
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor MEMBER m_backgroundColor WRITE setBackgroundColor DESIGNABLE true SCRIPTABLE true)

public:
    DLoadingIndicator(QWidget * parent = 0);
    DLoadingIndicator(QString loadingImgPath, QWidget * parent = 0);
    ~DLoadingIndicator();

    void setLoading(bool flag);
    void setLoadingPixmap(const QPixmap & loadingPixmap);

    void setAniDuration(int msecs);
    void setAniEasingCurve(const QEasingCurve & easing);
    void setBackgroundColor(const QColor &color);
    QColor getBackgroundColor();

public slots:
    void rotateImg(QVariant angle);

private:
    void initAniProperty();

    QColor m_backgroundColor;
    QPixmap m_loadingImg;
    QVariantAnimation m_rotateAni;
    QGraphicsPixmapItem * m_loadingImgItem;
};

DUI_END_NAMESPACE

#endif // DLOADINGINDICATOR_H
