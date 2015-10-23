#include "dcircleprogress.h"

#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

DCircleProgress::DCircleProgress(QWidget *parent)
    : QWidget(parent)
{
}

void DCircleProgress::setValue(int value)
{
    m_currentValue = value;
    update();

    emit valueChanged(value);
}

void DCircleProgress::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setRenderHints(QPainter::HighQualityAntialiasing);

    QPen pen(m_chunkColor);
    pen.setWidth(m_lineWidth);
    p.setPen(pen);
    QRect outerCircleRect = rect();
    outerCircleRect.setWidth(outerCircleRect.width() - (m_lineWidth - 1) * 2);
    outerCircleRect.setHeight(outerCircleRect.height() - (m_lineWidth - 1) * 2);
    if (outerCircleRect.width() < outerCircleRect.height())
        outerCircleRect.setHeight(outerCircleRect.width());
    else
        outerCircleRect.setWidth(outerCircleRect.height());
    outerCircleRect.setTop((rect().height() - outerCircleRect.height()) / 2);
    outerCircleRect.setLeft((rect().width() - outerCircleRect.width()) / 2);

    const double percent = double(m_currentValue) / (m_maximumValue - m_minmumValue);
    const int splitPos = -percent * 16 * 360;
    p.drawArc(outerCircleRect, 90 * 16, splitPos);
    pen.setColor(m_backgroundColor);
    p.setPen(pen);
    p.drawArc(outerCircleRect, 90 * 16, 16 * 360 + splitPos);

    QWidget::paintEvent(e);
}

