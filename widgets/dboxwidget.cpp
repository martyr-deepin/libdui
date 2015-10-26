/*!
    \class DBoxWidget
    \brief The DBoxWidget widget provides a Adaptive child widget size
    when child widget size changed.

    \inmodule libdui
*/

#include <QBoxLayout>
#include <QEvent>
#include <QDebug>
#include <QResizeEvent>

#include "dboxwidget.h"
#include "private/dboxwidget_p.h"

DUI_BEGIN_NAMESPACE

DBoxWidgetPrivate::DBoxWidgetPrivate(DBoxWidget *qq):
    DObjectPrivate(qq),
    layout(new QBoxLayout(QBoxLayout::TopToBottom))
{

}

void DBoxWidgetPrivate::init()
{
    Q_Q(DBoxWidget);

    layout->setMargin(0);
    layout->setSpacing(0);

    q->setLayout(layout);
}

DBoxWidget::DBoxWidget(QBoxLayout::Direction direction, QWidget *parent):
    QWidget(parent),
    DObject(*new DBoxWidgetPrivate(this))
{
    d_func()->layout->setDirection(direction);
    d_func()->init();
}

QBoxLayout::Direction DBoxWidget::direction() const
{
    Q_D(const DBoxWidget);

    return d->layout->direction();
}

QBoxLayout *DBoxWidget::layout() const
{
    Q_D(const DBoxWidget);

    return d->layout;
}

void DBoxWidget::setDirection(QBoxLayout::Direction direction)
{
    Q_D(DBoxWidget);

    if (d->layout->direction() == direction)
        return;

    d->layout->setDirection(direction);
    emit directionChanged(direction);
}

bool DBoxWidget::event(QEvent *ee)
{
    if(ee->type() == QEvent::LayoutRequest) {
        Q_D(const DBoxWidget);

        setFixedSize(d->layout->sizeHint());
    } else if(ee->type() == QEvent::Resize) {
        emit sizeChanged(size());
    }

    return QWidget::event(ee);
}

DHBoxWidget::DHBoxWidget(QWidget *parent):
    DBoxWidget(QBoxLayout::LeftToRight, parent)
{

}

DVBoxWidget::DVBoxWidget(QWidget *parent):
    DBoxWidget(QBoxLayout::TopToBottom, parent)
{

}

DUI_END_NAMESPACE
