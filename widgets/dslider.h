#ifndef DSLIDER_H
#define DSLIDER_H

#include <QSlider>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSlider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(int handleType READ handleType)
public:
    enum HandleType {
        SharpHandler,
        RoundHandle
    };

    DSlider(QWidget * parent = 0);
    DSlider(Qt::Orientation orientation, QWidget * parent = 0);
    ~DSlider();

    int handleType() const;
    void setHandleType(HandleType handleType);

private:
    int m_handleType = RoundHandle;
};

DUI_END_NAMESPACE

#endif // DSLIDER_H
