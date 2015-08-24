#include "dscrollbar.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DScrollBar::DScrollBar(QWidget *parent) : QScrollBar(parent)
{
    D_THEME_INIT_WIDGET(DScrollBar);
}


DUI_END_NAMESPACE
