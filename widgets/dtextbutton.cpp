#include "dtextbutton.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DTextButton::DTextButton(const QString & text, QWidget * parent) :
    QPushButton(text, parent)
{
    D_THEME_INIT_WIDGET(DTextButton);
}

DTextButton::~DTextButton()
{

}

DUI_END_NAMESPACE
