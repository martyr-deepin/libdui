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
    Q_PROPERTY(bool loading READ loading WRITE setLoading)
    Q_PROPERTY(QPixmap imageSource MEMBER m_loadingImg READ imageSource WRITE setImageSource)
    Q_PROPERTY(QWidget* widgetSource READ widgetSource WRITE setWidgetSource)

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
    bool loading() const;
    QWidget* widgetSource() const;
    QPixmap imageSource() const;

public slots:
    void rotateImg(QVariant angle);
    void setWidgetSource(QWidget* widgetSource);
    void setImageSource(QPixmap imageSource);

private:
    void initAniProperty();
    void setLoadingItem(QGraphicsItem *item);

    QColor m_backgroundColor;
    QPixmap m_loadingImg;
    QVariantAnimation m_rotateAni;
    QGraphicsItem * m_loadingImgItem;
    bool m_loading;
    QWidget* m_widgetSource = NULL;
    QPixmap m_imageSource;
};

DUI_END_NAMESPACE

#endif // DLOADINGINDICATOR_H
