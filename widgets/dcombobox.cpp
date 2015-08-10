#include "dcombobox.h"
#include "dthememanager.h"

DUI_USE_NAMESPACE

DComboBox::DComboBox(QWidget *parent) : QComboBox(parent)
{
    D_THEME_INIT_WIDGET(DComboBox);
}


