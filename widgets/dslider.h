#ifndef DSLIDER_H
#define DSLIDER_H

#include <QSlider>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSlider : public QSlider
{
    Q_OBJECT
public:
    DSlider(QWidget * parent = 0);
    DSlider(Qt::Orientation orientation, QWidget * parent = 0);
    ~DSlider();
};

DUI_END_NAMESPACE

#endif // DSLIDER_H
