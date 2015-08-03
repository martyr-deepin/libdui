#ifndef SEGMENTEDCONTROL_H
#define SEGMENTEDCONTROL_H

#include <QFrame>
#include "dsegmentedcontrol.h"

class Segmentedcontrol : public QFrame
{
    Q_OBJECT
public:
    explicit Segmentedcontrol(QWidget *parent = 0);

private:
    DUI::DSegmentedControl *segmentedControl;
};

#endif // SEGMENTEDCONTROL_H
