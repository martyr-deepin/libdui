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

    m_scene->setSceneRect(0, 0, width(), height());
    setScene(m_scene);

    m_loadingImgItem = new QGraphicsPixmapItem(m_loadingImg);
    m_scene->addItem(m_loadingImgItem);

    m_loadingImgItem->setPos((width()-m_loadingImg.width())/2, \
                             (height()-m_loadingImg.height())/2);
    m_loadingImgItem->setTransformOriginPoint(m_loadingImg.width()/2, m_loadingImg.height()/2);

    initAniProperty();
    connect(&m_rotateAni, SIGNAL(valueChanged(QVariant)), this, SLOT(rotateImg(QVariant)));
}

DLoadingIndicator::~DLoadingIndicator()
{}

void DLoadingIndicator::initAniProperty(){
    m_rotateAni.setDuration(1000);
    m_rotateAni.setEasingCurve(QEasingCurve::OutInQuad);

    m_rotateAni.setLoopCount(-1);
    m_rotateAni.setStartValue(QVariant(qreal(0.0)));
    m_rotateAni.setEndValue(QVariant(qreal(360.0)));
}

void DLoadingIndicator::rotateImg(QVariant angle)
{
    m_loadingImgItem->setRotation(angle.toReal());
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

void DLoadingIndicator::setLoadingPixmap(const QPixmap &loadingPixmap)
{
    m_loadingImg = loadingPixmap;

    scene()->setSceneRect(0, 0, width(), height());

    m_loadingImgItem = new QGraphicsPixmapItem(m_loadingImg);
    scene()->addItem(m_loadingImgItem);

    m_loadingImgItem->setPos((width()-m_loadingImg.width())/2, \
                             (height()-m_loadingImg.height())/2);
    m_loadingImgItem->setTransformOriginPoint(m_loadingImg.width()/2, m_loadingImg.height()/2);
}

DUI_END_NAMESPACE
