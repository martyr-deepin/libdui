#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QTimer>

#include "dslider.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

static const int CustomDrawingLeftPadding = 10;
static const int CustomDrawingRightPadding = 10;
static const int CustomDrawingScaleHeight = 6;

// TODO: optimize for better vertical slider support
class DSliderPrivate
{
    DSliderPrivate(DSlider *q):
        m_hoverShowValue(false),
        m_handleHovering(false),
        m_hoverTimout(false),
        m_hoverShowValueInterval(-1),
        q_ptr(q)
    {
        m_hoverTimer.setSingleShot(true);
    }

    int m_handleType = DSlider::RoundHandle;

    QString m_leftTip;
    QString m_rightTip;
    QList<int> m_scales;

    QColor m_tipColor = Qt::black;
    QColor m_scaleColor = Qt::black;
    QColor m_hoverValueColor;
    bool m_hoverShowValue;
    bool m_handleHovering;
    bool m_hoverTimout;
    int m_hoverShowValueInterval;
    QTimer m_hoverTimer;

    int getScalePosition(int value);

    DSlider *q_ptr;
    Q_DECLARE_PUBLIC(DSlider)
};

DSlider::DSlider(QWidget *parent) :
    QSlider(parent),
    d_ptr(new DSliderPrivate(this))
{
    init();
}

DSlider::DSlider(Qt::Orientation orientation, QWidget *parent) :
    QSlider(orientation, parent),
    d_ptr(new DSliderPrivate(this))
{
    init();
}

DSlider::~DSlider()
{

}

int DSlider::handleType() const
{
    Q_D(const DSlider);

    return d->m_handleType;
}

void DSlider::setHandleType(HandleType handleType)
{
    Q_D(DSlider);

    d->m_handleType = handleType;
}


QString DSlider::rightTip() const
{
    Q_D(const DSlider);

    return d->m_rightTip;
}

void DSlider::setRightTip(const QString &rightTip)
{
    Q_D(DSlider);

    if (d->m_rightTip == rightTip) {
        return;
    }

    if (d->m_rightTip.isEmpty() || rightTip.isEmpty()) {
        d->m_rightTip = rightTip;
        updateGeometry();
    } else {
        d->m_rightTip = rightTip;
    }

    repaint();
}

QString DSlider::leftTip() const
{
    Q_D(const DSlider);

    return d->m_leftTip;
}

void DSlider::setLeftTip(const QString &leftTip)
{
    Q_D(DSlider);

    if (d->m_leftTip == leftTip) {
        return;
    }

    if (d->m_leftTip.isEmpty() || leftTip.isEmpty()) {
        d->m_leftTip = leftTip;
        updateGeometry();
    } else {
        d->m_leftTip = leftTip;
    }

    repaint();
}

QColor DSlider::scaleColor() const
{
    Q_D(const DSlider);

    return d->m_scaleColor;
}

void DSlider::setScaleColor(const QColor &scaleColor)
{
    Q_D(DSlider);

    d->m_scaleColor = scaleColor;

    repaint();
}

QColor DSlider::tipColor() const
{
    Q_D(const DSlider);

    return d->m_tipColor;
}

void DSlider::setTipColor(const QColor &tipColor)
{
    Q_D(DSlider);

    d->m_tipColor = tipColor;

    repaint();
}

void DSlider::addScale(int value)
{
    Q_D(DSlider);

    d->m_scales.append(value);

    if (d->m_scales.count() == 1) {
        updateGeometry();
    }

    repaint();
}

void DSlider::removeScale(int value)
{
    Q_D(DSlider);

    d->m_scales.removeOne(value);

    if (d->m_scales.isEmpty()) {
        updateGeometry();
    }

    repaint();
}

void DSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (orientation() == Qt::Vertical) {
            setValue(minimum() + ((maximum() - minimum()) * (height() - event->y())) / height()) ;
        } else {
            // FIXME
            // the value 10 is specified in DSlider.theme, it's ugly here, but I don't have any
            // good idea for now, maybe someone can help.
            setValue(minimum() + ((maximum() - minimum()) * (event->x() - 10)) / (width() - 10 - 10)) ;
        }

        event->accept();
    }

    QSlider::mousePressEvent(event);
}

void DSlider::paintEvent(QPaintEvent *event)
{
    Q_D(DSlider);

    QPainter painter;
    painter.begin(this);

    // draw tips
    QFont font = painter.font();
    font.setPixelSize(12);
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setColor(d->m_tipColor);
    painter.setPen(pen);

    QRect tmp = rect().adjusted(CustomDrawingLeftPadding - 5, 0, -CustomDrawingRightPadding + 5, 0);

    QTextOption leftBottomOption;
    leftBottomOption.setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    painter.drawText(tmp, d->m_leftTip, leftBottomOption);

    QTextOption rightBottomOption;
    rightBottomOption.setAlignment(Qt::AlignRight | Qt::AlignBottom);
    painter.drawText(tmp, d->m_rightTip, rightBottomOption);

    // draw scales
    pen.setColor(d->m_scaleColor);
    painter.setPen(pen);

    foreach(int scale, d->m_scales) {
        int x = d->getScalePosition(scale);
        int y = height() - 8;
        painter.drawLine(x, y, x, y - CustomDrawingScaleHeight);
    }

    if (d->m_handleHovering && !d->m_hoverTimout) {
        QString str = QString::number(value());
        int x = d->getScalePosition(value()) - painter.fontMetrics().width(str) / 2.0;
        painter.setPen(d->m_hoverValueColor);
        painter.drawText(x, 10, str);
    }

    painter.end();

    QSlider::paintEvent(event);
}

void DSlider::mouseMoveEvent(QMouseEvent *event)
{
    QSlider::mouseMoveEvent(event);

    Q_D(DSlider);

    if (!d->m_hoverShowValue) {
        return;
    }

    QPoint pos = event->pos();
    QRect rect(d->getScalePosition(value()) - CustomDrawingLeftPadding, 10, 20, 20);
    if (d->m_handleHovering) {
        d->m_handleHovering = rect.contains(pos);
    } else {
        d->m_handleHovering = rect.contains(pos);
        if (d->m_handleHovering) {
            d->m_hoverTimout = false;
            if (d->m_hoverShowValueInterval > 0) {
                d->m_hoverTimer.start(d->m_hoverShowValueInterval);
            }
        }
    }

    update();
}

void DSlider::hoverTimout()
{
    Q_D(DSlider);

    d->m_hoverTimout = true;
    update();
}

void DSlider::init()
{
    Q_D(DSlider);

    D_THEME_INIT_WIDGET(DSlider);

    setMouseTracking(true);
    connect(&d->m_hoverTimer, &QTimer::timeout, this, &DSlider::hoverTimout);
}

QSize DSlider::sizeHint() const
{
    Q_D(const DSlider);

    QSize size = QSlider::sizeHint();
    if (!d->m_leftTip.isEmpty() || !d->m_rightTip.isEmpty() || !d->m_scales.isEmpty()) {
        size.setHeight(size.height() + 25);
    } else {
        if (d->m_hoverShowValue) {
            size.setHeight(size.height() + 25);
        } else {
            size.setHeight(size.height() + 3);
        }
    }

    return size;
}

bool DSlider::hoverShowValue() const
{
    Q_D(const DSlider);

    return d->m_hoverShowValue;
}

QColor DSlider::hoverValueColor() const
{
    Q_D(const DSlider);

    return d->m_hoverValueColor;
}

int DSlider::hoverShowValueInterval() const
{
    Q_D(const DSlider);

    return d->m_hoverShowValueInterval;
}

void DSlider::setHoverShowValue(bool hoverShowValue)
{
    Q_D(DSlider);

    if (d->m_hoverShowValue == hoverShowValue) {
        return;
    }

    d->m_hoverShowValue = hoverShowValue;
    d->m_handleHovering &= hoverShowValue;

    updateGeometry();
    repaint();
}

void DSlider::setHoverValueColor(QColor hoverValueColor)
{
    Q_D(DSlider);

    d->m_hoverValueColor = hoverValueColor;
}

void DSlider::setHoverShowValueInterval(int hoverShowValueInterval)
{
    Q_D(DSlider);

    d->m_hoverShowValueInterval = hoverShowValueInterval;
}

DSlider::DSlider(DSliderPrivate &d): d_ptr(&d)
{
    init();
}

int DSliderPrivate::getScalePosition(int value)
{
    Q_Q(DSlider);

    float valueRange = q->maximum() - q->minimum();
    float posRange = q->width() - CustomDrawingLeftPadding - CustomDrawingRightPadding;
    return CustomDrawingLeftPadding + (value - q->minimum()) * posRange / valueRange;
}

DUI_END_NAMESPACE
