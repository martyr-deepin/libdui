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
}

