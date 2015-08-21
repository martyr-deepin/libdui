#include "dlinkbutton.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DUI::DLinkButton::DLinkButton(const QString &text, QWidget *parent) :
    QPushButton(text, parent)
{
    D_THEME_INIT_WIDGET(DLinkButton);
}

DUI_END_NAMESPACE
