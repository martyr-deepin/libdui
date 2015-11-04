#include "dcheckbox.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DCheckBox::DCheckBox(QWidget *parent) :
    QCheckBox(parent)
{
    D_THEME_INIT_WIDGET(DCheckBox)
}

DCheckBox::DCheckBox(const QString &text, QWidget *parent):
    QCheckBox(text, parent)
{
    D_THEME_INIT_WIDGET(DCheckBox)
}

DUI_END_NAMESPACE
