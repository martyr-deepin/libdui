#ifndef DLINEEDIT_P_H
#define DLINEEDIT_P_H

#include "dlineedit.h"
#include "dobject_p.h"
#include "dimagebutton.h"

#include <QHBoxLayout>

DUI_BEGIN_NAMESPACE

class DLineEditPrivate : public DObjectPrivate
{
    Q_DECLARE_PUBLIC(DLineEdit)

public:
    DLineEditPrivate(DLineEdit *q);

    void init();

public slots:
    void _q_resizeInsideFrame(const QSize &size);
    void _q_resizeInputableRegion();

public:
    bool m_isAlert = false;

    QFrame *m_insideFrame;
    DImageButton *m_rightIcon;
    QHBoxLayout *m_centeralHLayout;
};

DUI_END_NAMESPACE

#endif // DLINEEDIT_P_H

