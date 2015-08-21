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
    m_rightTip = rightTip;

    repaint();
}

QString DSlider::leftTip() const
{
    return m_leftTip;
}

void DSlider::setLeftTip(const QString &leftTip)
{
    m_leftTip = leftTip;

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

    repaint();
}

void DSlider::removeScale(int value)
{
    m_scales.removeOne(value);

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

int DSlider::getScalePosition(int value)
{
    float valueRange = maximum() - minimum();
    float posRange = width() - CustomDrawingLeftPadding - CustomDrawingRightPadding;
    return CustomDrawingLeftPadding + value * posRange / valueRange;
}

DUI_END_NAMESPACE
