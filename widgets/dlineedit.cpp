#include "dlineedit.h"
#include "dthememanager.h"

DUI_USE_NAMESPACE

DLineEdit::DLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    D_THEME_INIT_WIDGET(DLineEdit, alert);
}

void DLineEdit::setAlert(bool isAlert)
{
    if (m_isAlert == isAlert)
        return;
    m_isAlert = isAlert;
    emit alertChanged();
}

