#include "dslider.h"
#include "slidertab.h"

DUI_USE_NAMESPACE

SliderTab::SliderTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("SliderTab{background-color:  #1A1B1B}");

    DSlider * slider = new DSlider(Qt::Horizontal, this);
    slider->setFixedWidth(300);
    slider->setFixedHeight(40);
    slider->move(20, 50);

    DSlider *sharpSlider = new DSlider(Qt::Horizontal, this);
    sharpSlider->setHandleType(DSlider::SharpHandler);
    sharpSlider->setFixedWidth(300);
    sharpSlider->setFixedHeight(40);
    sharpSlider->move(20, 100);

}

