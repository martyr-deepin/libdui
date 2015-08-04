#include "dslider.h"
#include "slidertab.h"

DUI_USE_NAMESPACE

SliderTab::SliderTab(QWidget *parent) : QWidget(parent)
{
    DSlider * slider = new DSlider(Qt::Horizontal, this);
    slider->setFixedWidth(300);
    slider->move(5, 100);
}

