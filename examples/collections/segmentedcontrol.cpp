#include "segmentedcontrol.h"
#include <QLabel>

Segmentedcontrol::Segmentedcontrol(QWidget *parent) :
    QFrame(parent),
    segmentedControl(new DUI::DSegmentedControl(this))
{
    setStyleSheet("Segmentedcontrol{background: #1e1e1e;}");

    segmentedControl->addSegmented("page1");
    segmentedControl->addSegmented("page2");
    segmentedControl->addSegmented("page3");
    segmentedControl->move(100, 50);

    QLabel *label = new QLabel(this);
    QPalette pa = label->palette();
    pa.setColor(QPalette::Foreground, Qt::white);
    label->setPalette(pa);
    label->move(100, 150);
    label->setText(QString("current paga %1").arg(segmentedControl->currentIndex())+1);

    connect(segmentedControl, &DUI::DSegmentedControl::currentChanged, [=](){
        label->setText(QString("current paga %1").arg(segmentedControl->currentIndex())+1);
    });
}

