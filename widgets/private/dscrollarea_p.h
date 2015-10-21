#ifndef DSCROLLAREA_P_H
#define DSCROLLAREA_P_H

#include "libdui_global.h"
#include "dscrollarea.h"
#include "dobject_p.h"

class QPropertyAnimation;

DUI_BEGIN_NAMESPACE

class DScrollAreaPrivate : public DObjectPrivate
{
protected:
    DScrollAreaPrivate(DScrollArea *qq);
    ~DScrollAreaPrivate();

private:
    void init();

    bool autoHideScrollBar;
    DScrollBar *vBar;
    DScrollBar *hBar;
    QPropertyAnimation *scrollBarAnimation;
    QTimer *timer;

    D_DECLARE_PUBLIC(DScrollArea)
};

DUI_END_NAMESPACE

#endif // DSCROLLAREA_P_H
