#include "darrowrectangle.h"

DUI_USE_NAMESPACE

DArrowRectangle::DArrowRectangle(ArrowDirection direction, QWidget * parent) :
    QWidget(parent),m_arrowDirection(direction)
{
    D_THEME_INIT_WIDGET(DArrowRectangle);

    setWindowFlags(Qt::SplashScreen);
    setAttribute(Qt::WA_TranslucentBackground);
}

void DArrowRectangle::show(int x, int y)
{
    m_lastPos = QPoint(x, y);
    move(x, y);//Overload function
    if (isHidden())
        QWidget::show();

    resizeWithContent();
    repaint();
}

void DArrowRectangle::setContent(QWidget *content)
{
    if (!content)
        return;

    m_content = content;
    m_content->setParent(this);

    resizeWithContent();
    switch(m_arrowDirection)
    {
    case ArrowLeft:
        m_content->move(m_arrowHeight + m_margin,m_margin);
        break;
    case ArrowRight:
        m_content->move(m_margin,m_margin);
        break;
    case ArrowTop:
        m_content->move(m_margin,m_margin + m_arrowHeight);
        break;
    case ArrowBottom:
        m_content->move(m_margin,m_margin);
        break;
    }

    repaint();
}

void DArrowRectangle::resizeWithContent()
{
    setFixedSize(getFixedSize());

    repaint();
}

QSize DArrowRectangle::getFixedSize()
{
    if (m_content)
    {
        switch(m_arrowDirection)
        {
        case ArrowLeft:
        case ArrowRight:
            return QSize(m_content->width() + m_margin * 2 + m_arrowHeight,m_content->height() + m_margin * 2);
        case ArrowTop:
        case ArrowBottom:
            return QSize(m_content->width() + m_margin * 2,m_content->height() + m_margin * 2 + m_arrowHeight);
        }
    }
    else
        return QSize(0, 0);
}

void DArrowRectangle::move(int x, int y)
{
    QDesktopWidget dw;
    QRect dRect = dw.screenGeometry();

    int xLeftValue = x - width() / 2;
    int xRightValue = x + width() / 2 - dRect.width();
    int yTopValue = y - m_arrowY;
    int yBottomValue = y + (height() - m_arrowY);
    switch (m_arrowDirection)
    {
    case ArrowLeft:
        if (yTopValue < dRect.y())
        {
            setArrowY(m_arrowWidth / 2);
            yTopValue = dRect.y();
        }
        else if (yBottomValue > (dRect.height() + dRect.y()))
        {
            setArrowY((dRect.height() + dRect.y()) - m_arrowWidth / 2);
            yTopValue = dRect.height() - height();
        }
        QWidget::move(x,yTopValue);
        break;
    case ArrowRight:
        if (yTopValue < dRect.y())
        {
            setArrowY(m_arrowWidth / 2);
            yTopValue = dRect.y();
        }
        else if (yBottomValue > (dRect.height() + dRect.y()))
        {
            setArrowY((dRect.height() + dRect.y()) - m_arrowWidth / 2);
            yTopValue = dRect.height() - height();
        }
        QWidget::move(x - width(),yTopValue);
        break;
    case ArrowTop:
        if (xLeftValue < dRect.x())//out of screen in left side
        {
            setArrowX(width() / 2 + xLeftValue);
            xLeftValue = dRect.x();
        }
        else if(xRightValue > 0)//out of screen in right side
        {
            setArrowX(width() / 2 + xRightValue);
            xLeftValue = dRect.width() - width();
        }
        QWidget::move(xLeftValue,y);
        break;
    case ArrowBottom:
        if (xLeftValue < dRect.x())//out of screen in left side
        {
            setArrowX(width() / 2 + xLeftValue);
            xLeftValue = dRect.x();
        }
        else if(xRightValue > 0)//out of screen in right side
        {
            setArrowX(width() / 2 + xRightValue);
            xLeftValue = dRect.width() - width();
        }
        QWidget::move(xLeftValue,y - height());
        break;
    default:
        QWidget::move(x,y);
        break;
    }

}

// override methods
void DArrowRectangle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath border;

    switch (m_arrowDirection)
    {
    case DArrowRectangle::ArrowLeft:
        border = getLeftCornerPath();
        break;
    case DArrowRectangle::ArrowRight:
        border = getRightCornerPath();
        break;
    case DArrowRectangle::ArrowTop:
        border = getTopCornerPath();
        break;
    case DArrowRectangle::ArrowBottom:
        border = getBottomCornerPath();
        break;
    default:
        border = getRightCornerPath();
    }

    painter.setClipPath(border);
    painter.fillPath(border, QBrush(m_backgroundColor));

    QPen strokePen;
    strokePen.setColor(m_borderColor);
    strokePen.setWidth(m_borderWidth);
    painter.strokePath(border, strokePen);
}
QColor DArrowRectangle::borderColor() const
{
    return m_borderColor;
}

void DArrowRectangle::setBorderColor(const QColor &borderColor)
{
    m_borderColor = borderColor;
}

int DArrowRectangle::borderWidth() const
{
    return m_borderWidth;
}

void DArrowRectangle::setBorderWidth(int borderWidth)
{
    m_borderWidth = borderWidth;
}

QColor DArrowRectangle::backgroundColor() const
{
    return m_backgroundColor;
}

void DArrowRectangle::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

int DArrowRectangle::radius() const
{
    return this->m_radius;
}

int DArrowRectangle::arrowHeight() const
{
    return this->m_arrowHeight;
}

int DArrowRectangle::arrowWidth() const
{
    return this->m_arrowWidth;
}

int DArrowRectangle::arrowX() const
{
    return this->m_arrowX;
}

int DArrowRectangle::arrowY() const
{
    return this->m_arrowY;
}

int DArrowRectangle::margin() const
{
    return this->m_margin;
}

void DArrowRectangle::setArrorDirection(ArrowDirection value)
{
    m_arrowDirection = value;
}

void DArrowRectangle::setWidth(int value)
{
    this->setFixedWidth(value);
}

void DArrowRectangle::setHeight(int value)
{
    this->setFixedHeight(value);
}

void DArrowRectangle::setRadius(int value)
{
    this->m_radius = value;
}

void DArrowRectangle::setArrowHeight(int value)
{
    this->m_arrowHeight = value;
}

void DArrowRectangle::setArrowWidth(int value)
{
    this->m_arrowWidth = value;
}

void DArrowRectangle::setArrowX(int value)
{
    if (value < m_arrowWidth / 2)
        this->m_arrowX = m_arrowWidth / 2;
    else if (value > (width() - m_arrowWidth / 2))
        this->m_arrowX = width() - m_arrowWidth / 2;
    else
        this->m_arrowX = value;
}

void DArrowRectangle::setArrowY(int value)
{
    if (value < m_arrowHeight / 2)
        this->m_arrowY = m_arrowHeight / 2;
    else if (value > (height() - m_arrowHeight / 2))
        this->m_arrowY = height() - m_arrowHeight / 2;
    else
        this->m_arrowY = value;

}

void DArrowRectangle::setMargin(int value)
{
    this->m_margin = value;
}

QPainterPath DArrowRectangle::getLeftCornerPath()
{
    QRect rect = this->rect().marginsRemoved(QMargins(m_shadowWidth,m_shadowWidth,m_shadowWidth,m_shadowWidth));

    QPoint cornerPoint(rect.x(), rect.y() + (m_arrowY > 0 ? m_arrowY : (rect.height() / 2)));
    QPoint topLeft(rect.x() + m_arrowHeight, rect.y());
    QPoint topRight(rect.x() + rect.width(), rect.y());
    QPoint bottomRight(rect.x() + rect.width(), rect.y() + rect.height());
    QPoint bottomLeft(rect.x() + m_arrowHeight, rect.y() + rect.height());
    int radius = this->m_radius > (rect.height() / 2) ? (rect.height() / 2) : this->m_radius;

    QPainterPath border;
    border.moveTo(topLeft.x() - radius,topLeft.y());
    border.lineTo(topRight.x() - radius, topRight.y());
    border.arcTo(topRight.x() - 2 * radius, topRight.y(), 2 * radius, 2 * radius, 90, -90);
    border.lineTo(bottomRight.x(), bottomRight.y() - radius);
    border.arcTo(bottomRight.x() - 2 * radius, bottomRight.y() - 2 * radius, 2 * radius, 2 * radius, 0, -90);
    border.lineTo(bottomLeft.x() - radius,bottomLeft.y());
    border.arcTo(bottomLeft.x(),bottomLeft.y() - 2 * radius,2 * radius,2 * radius,-90,-90);
    border.lineTo(cornerPoint.x() + m_arrowHeight,cornerPoint.y() + m_arrowWidth / 2);
    border.lineTo(cornerPoint);
    border.lineTo(cornerPoint.x() + m_arrowHeight,cornerPoint.y() - m_arrowWidth / 2);
    border.lineTo(topLeft.x(),topLeft.y() + radius);
    border.arcTo(topLeft.x(),topLeft.y(),2 * radius,2 * radius,-180,-90);
    border.lineTo(topLeft.x() - radius,topLeft.y());

    return border;
}

QPainterPath DArrowRectangle::getRightCornerPath()
{
    QRect rect = this->rect().marginsRemoved(QMargins(m_shadowWidth,m_shadowWidth,m_shadowWidth,m_shadowWidth));

    QPoint cornerPoint(rect.x() + rect.width(), rect.y() + (m_arrowY > 0 ? m_arrowY : rect.height() / 2));
    QPoint topLeft(rect.x(), rect.y());
    QPoint topRight(rect.x() + rect.width() - m_arrowHeight, rect.y());
    QPoint bottomRight(rect.x() + rect.width() - m_arrowHeight, rect.y() + rect.height());
    QPoint bottomLeft(rect.x(), rect.y() + rect.height());
    int radius = this->m_radius > (rect.height() / 2) ? rect.height() / 2 : this->m_radius;

    QPainterPath border;
    border.moveTo(topLeft.x() + radius, topLeft.y());
    border.lineTo(topRight.x() - radius,topRight.y());
    border.arcTo(topRight.x() - 2 * radius,topRight.y(),2 * radius,2 * radius,90,-90);
    border.lineTo(cornerPoint.x() - m_arrowHeight,cornerPoint.y() - m_arrowWidth / 2);
    border.lineTo(cornerPoint);
    border.lineTo(cornerPoint.x() - m_arrowHeight,cornerPoint.y() + m_arrowWidth / 2);
    border.lineTo(bottomRight.x(),bottomRight.y() - radius);
    border.arcTo(bottomRight.x() - 2 * radius,bottomRight.y() - 2 * radius,2 * radius,2 * radius,0,-90);
    border.lineTo(bottomLeft.x() + radius, bottomLeft.y());
    border.arcTo(bottomLeft.x(), bottomLeft.y() - 2 * radius, 2 * radius, 2 * radius, -90, -90);
    border.lineTo(topLeft.x(), topLeft.y() + radius);
    border.arcTo(topLeft.x(), topLeft.y(), 2 * radius, 2 * radius, 180, -90);

    return border;
}

QPainterPath DArrowRectangle::getTopCornerPath()
{
    QRect rect = this->rect().marginsRemoved(QMargins(m_shadowWidth,m_shadowWidth,m_shadowWidth,m_shadowWidth));

    QPoint cornerPoint(rect.x() + (m_arrowX > 0 ? m_arrowX : rect.width() / 2), rect.y());
    QPoint topLeft(rect.x(), rect.y() + m_arrowHeight);
    QPoint topRight(rect.x() + rect.width(), rect.y() + m_arrowHeight);
    QPoint bottomRight(rect.x() + rect.width(), rect.y() + rect.height());
    QPoint bottomLeft(rect.x(), rect.y() + rect.height());
    int radius = this->m_radius > (rect.height() / 2 - m_arrowHeight) ? rect.height() / 2 -m_arrowHeight : this->m_radius;

    QPainterPath border;
    border.moveTo(topLeft.x() + radius, topLeft.y());
    border.lineTo(cornerPoint.x() - m_arrowWidth / 2, cornerPoint.y() + m_arrowHeight);
    border.lineTo(cornerPoint);
    border.lineTo(cornerPoint.x() + m_arrowWidth / 2, cornerPoint.y() + m_arrowHeight);
    border.lineTo(topRight.x() - radius, topRight.y());
    border.arcTo(topRight.x() - 2 * radius, topRight.y(), 2 * radius, 2 * radius, 90, -90);
    border.lineTo(bottomRight.x(), bottomRight.y() - radius);
    border.arcTo(bottomRight.x() - 2 * radius, bottomRight.y() - 2 * radius, 2 * radius, 2 * radius, 0, -90);
    border.lineTo(bottomLeft.x() + radius, bottomLeft.y());
    border.arcTo(bottomLeft.x(), bottomLeft.y() - 2 * radius, 2 * radius, 2 * radius, - 90, -90);
    border.lineTo(topLeft.x(), topLeft.y() + radius);
    border.arcTo(topLeft.x(), topLeft.y(), 2 * radius, 2 * radius, 180, -90);

    return border;
}

QPainterPath DArrowRectangle::getBottomCornerPath()
{
    QRect rect = this->rect().marginsRemoved(QMargins(m_shadowWidth,m_shadowWidth,m_shadowWidth,m_shadowWidth));

    QPoint cornerPoint(rect.x() + (m_arrowX > 0 ? m_arrowX : rect.width() / 2), rect.y()  + rect.height());
    QPoint topLeft(rect.x(), rect.y());
    QPoint topRight(rect.x() + rect.width(), rect.y());
    QPoint bottomRight(rect.x() + rect.width(), rect.y() + rect.height() - m_arrowHeight);
    QPoint bottomLeft(rect.x(), rect.y() + rect.height() - m_arrowHeight);
    int radius = this->m_radius > (rect.height() / 2 - m_arrowHeight) ? rect.height() / 2 -m_arrowHeight : this->m_radius;

    QPainterPath border;
    border.moveTo(topLeft.x() + radius, topLeft.y());
    border.lineTo(topRight.x() - radius, topRight.y());
    border.arcTo(topRight.x() - 2 * radius, topRight.y(), 2 * radius, 2 * radius, 90, -90);
    border.lineTo(bottomRight.x(), bottomRight.y() - radius);
    border.arcTo(bottomRight.x() - 2 * radius, bottomRight.y() - 2 * radius, 2 * radius, 2 * radius, 0, -90);
    border.lineTo(cornerPoint.x() + m_arrowWidth / 2, cornerPoint.y() - m_arrowHeight);
    border.lineTo(cornerPoint);
    border.lineTo(cornerPoint.x() - m_arrowWidth / 2, cornerPoint.y() - m_arrowHeight);
    border.lineTo(bottomLeft.x() + radius, bottomLeft.y());
    border.arcTo(bottomLeft.x(), bottomLeft.y() - 2 * radius, 2 * radius, 2 * radius, -90, -90);
    border.lineTo(topLeft.x(), topLeft.y() + radius);
    border.arcTo(topLeft.x(), topLeft.y(), 2 * radius, 2 * radius, 180, -90);

    return border;
}

DArrowRectangle::~DArrowRectangle()
{

}

