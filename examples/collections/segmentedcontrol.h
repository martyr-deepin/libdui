#ifndef SEGMENTEDCONTROL_H
#define SEGMENTEDCONTROL_H

#include <QFrame>
#include "dsegmentedcontrol.h"
#include "libdui_global.h"

DUI_USE_NAMESPACE

class Segmentedcontrol : public QFrame
{
    Q_OBJECT
public:
    explicit Segmentedcontrol(QWidget *parent = 0);

private:
    DSegmentedControl *segmentedControl;
};

#endif // SEGMENTEDCONTROL_H
