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

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(bool loading READ loading WRITE setLoading)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth)
    Q_PROPERTY(QPixmap imageSource READ imageSource WRITE setImageSource)
    Q_PROPERTY(QWidget* widgetSource READ widgetSource WRITE setWidgetSource)
    Q_PROPERTY(int aniDuration READ aniDuration WRITE setAniDuration)
    Q_PROPERTY(QEasingCurve::Type aniEasingType READ aniEasingType WRITE setAniEasingType)

public:
    DLoadingIndicator(QWidget * parent = 0);
    ~DLoadingIndicator();

    QColor backgroundColor() const;
    bool loading() const;
    QWidget* widgetSource() const;
    QPixmap imageSource() const;
    int aniDuration() const;
    QEasingCurve::Type aniEasingType() const;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    bool smooth() const;

public slots:
    void setLoading(bool flag);
    void setAniDuration(int msecs);
    void setAniEasingCurve(const QEasingCurve & easing);
    void setBackgroundColor(const QColor &color);
    void setRotate(QVariant angle);
    void setWidgetSource(QWidget* widgetSource);
    void setImageSource(const QPixmap &imageSource);
    void setAniEasingType(QEasingCurve::Type aniEasingType);
    void setSmooth(bool smooth);

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    void initAniProperty();
    void setLoadingItem(QGraphicsItem *item);

    QVariantAnimation m_rotateAni;
    bool m_loading;
    QWidget* m_widgetSource = NULL;
    bool m_smooth = false;
};

DUI_END_NAMESPACE

#endif // DLOADINGINDICATOR_H
