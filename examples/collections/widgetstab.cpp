#include "widgetstab.h"

WidgetsTab::WidgetsTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("WidgetsTab {background-color:#252627;}");

    DUI::DCalendar *calendar = new DUI::DCalendar(this);
    calendar->setFixedSize(300, 300);
    calendar->move(8, 8);

    DUI::DTextButton *showLunar = new DUI::DTextButton("showLunar", this);
    showLunar->move(320, 50);

    DUI::DTextButton *hideLunar = new DUI::DTextButton("hideLunar", this);
    hideLunar->move(320, 80);

    connect(showLunar, &DUI::DTextButton::clicked, [calendar] () -> void {calendar->setLunarVisible(true);});
    connect(hideLunar, &DUI::DTextButton::clicked, [calendar] () -> void {calendar->setLunarVisible(false);});


    ////////////////////ArrowRectangle//////////////////
    DArrowRectangle *rectangle = new DArrowRectangle(DArrowRectangle::ArrowLeft);
//    rectangle->setArrowY(15);
    rectangle->setArrowX(25);
    rectangle->setArrowWidth(30);
    rectangle->setArrowHeight(10);
    QPushButton *button = new QPushButton("DArrowRectangle Test");
    button->setFixedSize(200, 30);
    rectangle->setContent(button);
    rectangle->show(200, 200);
}

