#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#include "dslider.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

static const int CustomDrawingLeftPadding = 10;
static const int CustomDrawingRightPadding = 10;
static const int CustomDrawingScaleHeight = 6;

DSlider::DSlider(QWidget * parent) :
    QSlider(parent)
{
    D_THEME_INIT_WIDGET(DSlider);
}

DSlider::DSlider(Qt::Orientation orientation, QWidget * parent) :
    QSlider(orientation, parent)
{
    D_THEME_INIT_WIDGET(DSlider);
}

DSlider::~DSlider()
{

}

int DSlider::handleType() const
{
    return m_handleType;
}

void DSlider::setHandleType(HandleType handleType)
{
    m_handleType = handleType;
}


QString DSlider::rightTip() const
{
    return m_rightTip;
}

void DSlider::setRightTip(const QString &rightTip)
{
    if(m_rightTip == rightTip)
        return;

    if(m_rightTip.isEmpty() || rightTip.isEmpty()){
        m_rightTip = rightTip;
        updateGeometry();
    }else{
        m_rightTip = rightTip;
    }

    repaint();
}

QString DSlider::leftTip() const
{
    return m_leftTip;
}

void DSlider::setLeftTip(const QString &leftTip)
{
    if(m_leftTip == leftTip)
        return;

    if(m_leftTip.isEmpty() || leftTip.isEmpty()){
        m_leftTip = leftTip;
        updateGeometry();
    }else{
        m_leftTip = leftTip;
    }

    repaint();
}

QColor DSlider::scaleColor() const
{
    return m_scaleColor;
}

void DSlider::setScaleColor(const QColor &scaleColor)
{
    m_scaleColor = scaleColor;

    repaint();
}

QColor DSlider::tipColor() const
{
    return m_tipColor;
}

void DSlider::setTipColor(const QColor &tipColor)
{
    m_tipColor = tipColor;

    repaint();
}

void DSlider::addScale(int value)
{
    m_scales.append(value);

    if(m_scales.count() == 1)
        updateGeometry();

    repaint();
}

void DSlider::removeScale(int value)
{
    m_scales.removeOne(value);

    if(m_scales.isEmpty())
        updateGeometry();

    repaint();
}

void DSlider::paintEvent(QPaintEvent * event)
{
    QSlider::paintEvent(event);

    QPainter painter;
    painter.begin(this);

    // draw tips
    QFont font = painter.font();
    font.setPixelSize(12);
    painter.setFont(font);

    QPen pen = painter.pen();
    pen.setColor(m_tipColor);
    painter.setPen(pen);

    QRect tmp = rect().adjusted(CustomDrawingLeftPadding - 5, 0, -CustomDrawingRightPadding + 5, 0);

    QTextOption leftBottomOption;
    leftBottomOption.setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    painter.drawText(tmp, m_leftTip, leftBottomOption);

    QTextOption rightBottomOption;
    rightBottomOption.setAlignment(Qt::AlignRight | Qt::AlignBottom);
    painter.drawText(tmp, m_rightTip, rightBottomOption);

    // draw scales
    pen.setColor(m_scaleColor);
    painter.setPen(pen);

    foreach (int scale, m_scales) {
        int x = getScalePosition(scale);
        int y = height() - 8;
        painter.drawLine(x, y, x, y - CustomDrawingScaleHeight);
    }

    painter.end();
}

QSize DSlider::sizeHint() const
{
    QSize size = QSlider::sizeHint();
    if(!m_leftTip.isEmpty() || !m_rightTip.isEmpty() || !m_scales.isEmpty())
        size.setHeight(size.height()+25);
    else
        size.setHeight(size.height()+3);
    return size;
}

int DSlider::getScalePosition(int value)
{
    float valueRange = maximum() - minimum();
    float posRange = width() - CustomDrawingLeftPadding - CustomDrawingRightPadding;
    return CustomDrawingLeftPadding + value * posRange / valueRange;
}

DUI_END_NAMESPACE
