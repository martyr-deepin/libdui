#include "dspinbox.h"
#include "dthememanager.h"
#include "dlineedit.h"

DUI_BEGIN_NAMESPACE

DSpinBox::DSpinBox(QWidget *parent) :
    QSpinBox(parent)
{
    D_THEME_INIT_WIDGET(DSpinBox);
}

QLineEdit *DSpinBox::lineEdit() const
{
    return QSpinBox::lineEdit();
}

DUI_END_NAMESPACE
