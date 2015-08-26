#ifndef WIDGETSTAB_H
#define WIDGETSTAB_H

#include <QLabel>

#include "dcalendar.h"
#include "dtextbutton.h"
#include "darrowrectangle.h"

DUI_USE_NAMESPACE

class WidgetsTab : public QLabel
{
    Q_OBJECT
public:
    explicit WidgetsTab(QWidget *parent = 0);
};

#endif // WIDGETSTAB_H
