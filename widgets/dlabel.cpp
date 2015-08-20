#include "dlabel.h"
#include "dthememanager.h"

DUI_USE_NAMESPACE

DLabel::DLabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    D_THEME_INIT_WIDGET(DLabel);
}


DLabel::DLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
{
    D_THEME_INIT_WIDGET(DLabel);
}

