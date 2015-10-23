#include "bartab.h"

#include "dcircleprogress.h"
#include "dslider.h"

BarTab::BarTab(QWidget *parent) : QFrame(parent)
{
    setStyleSheet("background-color:gray;");

    DCircleProgress *circleProgess = new DCircleProgress(this);
    circleProgess->setFixedSize(100, 100);
    circleProgess->move(50, 50);

    DUI::DSlider * slider = new DUI::DSlider(Qt::Horizontal, this);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setFixedWidth(100);
    slider->setFixedHeight(20);
    slider->move(50, 150);

    connect(slider, &DUI::DSlider::valueChanged, circleProgess, &DCircleProgress::setValue);
    connect(slider, &DUI::DSlider::valueChanged, [circleProgess] (const int value) {
        circleProgess->setText(QString::number(value) + "%");
    });
}

