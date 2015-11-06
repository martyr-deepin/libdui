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

void DBoxWidget::addWidget(QWidget *widget)
{
    layout()->addWidget(widget);
}

void DBoxWidget::setDirection(QBoxLayout::Direction direction)
{
    Q_D(DBoxWidget);

    if (d->layout->direction() == direction)
        return;

    d->layout->setDirection(direction);
    emit directionChanged(direction);
}

void DBoxWidget::updateSize(const QSize &size)
{
    if(direction() == QBoxLayout::TopToBottom || QBoxLayout::BottomToTop) {
        setFixedHeight(size.height());
        setMinimumWidth(size.width());
        setMaximumWidth(16777215);
    } else {
        setFixedWidth(size.width());
        setMinimumHeight(size.height());
        setMaximumHeight(16777215);
    }
}

bool DBoxWidget::event(QEvent *ee)
{
    Q_D(const DBoxWidget);

    if(ee->type() == QEvent::LayoutRequest) {
        if(size() != d->layout->sizeHint()) {
            updateSize(d->layout->sizeHint());
            updateGeometry();
        }
    } else if(ee->type() == QEvent::Resize) {
        emit sizeChanged(size());
    } else if(ee->type() == QEvent::ChildAdded) {
        updateSize(d->layout->sizeHint());
    } else if(ee->type() == QEvent::ChildRemoved) {
        updateSize(d->layout->sizeHint());
    } else if(ee->type() == QEvent::Show) {
        updateSize(d->layout->sizeHint());
    }

    return QWidget::event(ee);
}

QSize DBoxWidget::sizeHint() const
{
    Q_D(const DBoxWidget);

    return d->layout->sizeHint();
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
