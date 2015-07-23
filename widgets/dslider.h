#ifndef DSLIDER_H
#define DSLIDER_H

#include <QSlider>

#include "libdui_global.h"

class LIBDUISHARED_EXPORT DSlider : public QSlider
{
    Q_OBJECT
public:
    DSlider(QWidget * parent = 0);
    DSlider(Qt::Orientation orientation, QWidget * parent = 0);
    ~DSlider();
};

#endif // DSLIDER_H
