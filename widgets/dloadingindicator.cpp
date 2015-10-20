#include <QGraphicsProxyWidget>
#include <QLabel>

#include "dloadingindicator.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DLoadingIndicator::DLoadingIndicator(QWidget *parent) :
    QGraphicsView(parent)
{
    D_THEME_INIT_WIDGET(DLoadingIndicator);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setScene(new QGraphicsScene(this));

    initAniProperty();
    connect(&m_rotateAni, SIGNAL(valueChanged(QVariant)), this, SLOT(setRotate(QVariant)));
}

DLoadingIndicator::~DLoadingIndicator()
{
    m_widgetSource->deleteLater();
}

QColor DLoadingIndicator::backgroundColor() const
{
    return scene()->backgroundBrush().color();
}

void DLoadingIndicator::initAniProperty(){
    m_rotateAni.setDuration(1000);
    m_rotateAni.setEasingCurve(QEasingCurve::OutInQuad);

    m_rotateAni.setLoopCount(-1);
    m_rotateAni.setStartValue(QVariant(qreal(0.0)));
    m_rotateAni.setEndValue(QVariant(qreal(360.0)));
}

void DLoadingIndicator::setLoadingItem(QGraphicsItem *item)
{
    QSizeF itemSize = item->boundingRect().size();

    item->setPos((width()-itemSize.width())/2,
                             (height()-itemSize.height())/2);
    item->setTransformOriginPoint(itemSize.width()/2, itemSize.height()/2);

    scene()->clear();
    scene()->setSceneRect(0, 0, width(), height());
    scene()->addItem(item);
}

void DLoadingIndicator::setRotate(QVariant angle)
{
    if(!scene()->items().isEmpty())
        scene()->items().first()->setRotation(angle.toReal());
}

void DLoadingIndicator::setWidgetSource(QWidget *widgetSource)
{
    if(m_widgetSource)
        m_widgetSource->deleteLater();

    m_widgetSource = widgetSource;

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget;
    proxy->setWidget(widgetSource);
    setLoadingItem(proxy);
}

void DLoadingIndicator::setImageSource(const QPixmap &imageSource)
{
    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(imageSource);
    if(m_smooth)
        item->setTransformationMode(Qt::SmoothTransformation);
    setLoadingItem(item);
}

void DLoadingIndicator::setAniEasingType(QEasingCurve::Type aniEasingType)
{
    setAniEasingCurve(aniEasingType);
}

void DLoadingIndicator::setSmooth(bool smooth)
{
    if(m_smooth == smooth)
        return;

    m_smooth = smooth;

    QGraphicsPixmapItem * item = nullptr;

    if(!scene()->items().isEmpty())
        item = dynamic_cast<QGraphicsPixmapItem*>(scene()->items().first());

    if(smooth){
        setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
        if(item)
            item->setTransformationMode(Qt::SmoothTransformation);
    }else{
        setRenderHint(QPainter::SmoothPixmapTransform, false);
        setRenderHint(QPainter::Antialiasing, false);
        if(item)
            item->setTransformationMode(Qt::FastTransformation);
    }
}

void DLoadingIndicator::setLoading(bool flag)
{
    if (flag == true){
        m_rotateAni.start();
    } else {
        m_rotateAni.stop();
    }
}

void DLoadingIndicator::setAniDuration(int msecs)
{
    m_rotateAni.setDuration(msecs);
}

void DLoadingIndicator::setAniEasingCurve(const QEasingCurve & easing)
{
    m_rotateAni.setEasingCurve(easing);
}

void DLoadingIndicator::setBackgroundColor(const QColor &color)
{
    scene()->setBackgroundBrush(color);
}

bool DLoadingIndicator::loading() const
{
    return m_rotateAni.state() == QVariantAnimation::Running;
}

QWidget *DLoadingIndicator::widgetSource() const
{
    return m_widgetSource;
}

QPixmap DLoadingIndicator::imageSource() const
{
    QGraphicsPixmapItem * item = nullptr;

    if(!scene()->items().isEmpty())
        item = dynamic_cast<QGraphicsPixmapItem*>(scene()->items().first());

    return item ? item->pixmap() : QPixmap();
}

int DLoadingIndicator::aniDuration() const
{
    return m_rotateAni.duration();
}

QEasingCurve::Type DLoadingIndicator::aniEasingType() const
{
    return m_rotateAni.easingCurve().type();
}

QSize DLoadingIndicator::sizeHint() const
{
    return scene()->sceneRect().size().toSize();
}

bool DLoadingIndicator::smooth() const
{
    return m_smooth;
}

DUI_END_NAMESPACE
