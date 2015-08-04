#include "dlineedit.h"
#include "dthememanager.h"

DUI_USE_NAMESPACE

DLineEdit::DLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    D_THEME_INIT_WIDGET(DLineEdit);
}

