#include "dslider.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DSlider::DSlider(QWidget * parent) :
    QSlider(parent)
{
    D_THEME_INIT_WIDGET(DSlider);
}


DSlider::DSlider(Qt::Orientation orientation, QWidget * parent) :
    QSlider(orientation, parent)
{
    D_THEME_INIT_WIDGET(DSlider);
}

DSlider::~DSlider()
{

}

DUI_END_NAMESPACE
