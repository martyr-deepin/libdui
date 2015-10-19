#include <QGraphicsProxyWidget>

#include "dloadingindicator.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DLoadingIndicator::DLoadingIndicator(QWidget *parent) :
    QGraphicsView(parent)
{
    D_THEME_INIT_WIDGET(DLoadingIndicator);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_backgroundColor = QColor("white");

    QGraphicsScene *graphicsScene = new QGraphicsScene(this);
    setScene(graphicsScene);

    initAniProperty();
    connect(&m_rotateAni, SIGNAL(valueChanged(QVariant)), this, SLOT(rotateImg(QVariant)));
}

DLoadingIndicator::DLoadingIndicator(QString loadingImgPath, QWidget * parent) :
    QGraphicsView(parent)
{
    D_THEME_INIT_WIDGET(DLoadingIndicator);

    QPixmap m_loadingImg(loadingImgPath);

    this->setMinimumSize(m_loadingImg.size());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_backgroundColor = QColor("white");

    QGraphicsScene *m_scene = new QGraphicsScene(this);
    setScene(m_scene);

    m_loadingImgItem = new QGraphicsPixmapItem(m_loadingImg);
    setLoadingItem(m_loadingImgItem);

    initAniProperty();
    connect(&m_rotateAni, SIGNAL(valueChanged(QVariant)), this, SLOT(rotateImg(QVariant)));
}

DLoadingIndicator::~DLoadingIndicator()
{
    m_widgetSource->deleteLater();
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

    m_loadingImgItem = item;

    scene()->setSceneRect(0, 0, width(), height());
    scene()->clear();
    scene()->addItem(m_loadingImgItem);

    m_loadingImgItem->setPos((width()-itemSize.width())/2,
                             (height()-itemSize.height())/2);
    m_loadingImgItem->setTransformOriginPoint(itemSize.width()/2, itemSize.height()/2);
}

void DLoadingIndicator::rotateImg(QVariant angle)
{
    m_loadingImgItem->setRotation(angle.toReal());
}

void DLoadingIndicator::setWidgetSource(QWidget *widgetSource)
{
    if(m_widgetSource)
        m_widgetSource->deleteLater();

    m_widgetSource = widgetSource;

    scene()->clear();
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget;
    proxy->setWidget(widgetSource);
    setLoadingItem(proxy);
}

void DLoadingIndicator::setImageSource(QPixmap imageSource)
{
    setLoadingPixmap(imageSource);
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
    m_backgroundColor = color;
    scene()->setBackgroundBrush(QBrush(color));
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
    return m_loadingImg;
}

void DLoadingIndicator::setLoadingPixmap(const QPixmap &loadingPixmap)
{
    m_loadingImg = loadingPixmap;
    setLoadingItem(new QGraphicsPixmapItem(m_loadingImg));
}

DUI_END_NAMESPACE
