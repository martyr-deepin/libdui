#include <QResizeEvent>

#include "dspinbox.h"
#include "dthememanager.h"
#include "dlineedit.h"
#include "private/dspinbox_p.h"

DUI_BEGIN_NAMESPACE

DSpinBoxPrivate::DSpinBoxPrivate(DSpinBox *parent) :
    DObjectPrivate(parent)
{

}

void DSpinBoxPrivate::init()
{
    D_Q(DSpinBox);

    insideFrame = new QFrame(q);
    insideFrame->setObjectName("SpinBoxInsideFrame");
}

void DSpinBoxPrivate::_q_resizeInsideFrame(const QSize &size)
{
    insideFrame->setFixedWidth(size.width());
    insideFrame->setFixedHeight(size.height() - 1);
}

DSpinBox::DSpinBox(QWidget *parent) :
    QSpinBox(parent),
    DObject(*new DSpinBoxPrivate(this))
{
    D_THEME_INIT_WIDGET(DSpinBox);

    d_func()->init();
}

QLineEdit *DSpinBox::lineEdit() const
{
    return QSpinBox::lineEdit();
}

void DSpinBox::resizeEvent(QResizeEvent *e)
{
    QSpinBox::resizeEvent(e);

    d_func()->_q_resizeInsideFrame(e->size());
}

DUI::DDoubleSpinBoxPrivate::DDoubleSpinBoxPrivate(DDoubleSpinBox *parent) :
    DObjectPrivate(parent)
{

}

void DDoubleSpinBoxPrivate::init()
{
    D_Q(DDoubleSpinBox);

    insideFrame = new QFrame(q);
    insideFrame->setObjectName("SpinBoxInsideFrame");
}

void DDoubleSpinBoxPrivate::_q_resizeInsideFrame(const QSize &size)
{
    insideFrame->setFixedWidth(size.width());
    insideFrame->setFixedHeight(size.height() - 1);
}

DDoubleSpinBox::DDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent),
    DObject(*new DDoubleSpinBoxPrivate(this))
{
    D_THEME_INIT_WIDGET(DSpinBox);

    d_func()->init();
}

void DDoubleSpinBox::resizeEvent(QResizeEvent *e)
{
    QDoubleSpinBox::resizeEvent(e);

    d_func()->_q_resizeInsideFrame(e->size());
}

DUI_END_NAMESPACE
