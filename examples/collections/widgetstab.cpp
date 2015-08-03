#include "widgetstab.h"

WidgetsTab::WidgetsTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("WidgetsTab {background-color:#252627;}");

    DUI::DCalendar *calendar = new DUI::DCalendar(this);
    calendar->setFixedSize(300, 300);
    calendar->move(8, 8);
}

