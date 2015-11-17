#ifndef DLINEEDIT_P_H
#define DLINEEDIT_P_H

#include "libdui_global.h"
#include "dlineedit.h"
#include "dobject_p.h"

#include <QHBoxLayout>

DUI_BEGIN_NAMESPACE

class DLineEditPrivate : DObjectPrivate
{
    Q_DECLARE_PUBLIC(DLineEdit)

public:
    DLineEditPrivate(DLineEdit *q);

public:
    bool m_isAlert = false;

    QHBoxLayout *m_centeralLayout;
};

DUI_END_NAMESPACE

#endif // DLINEEDIT_P_H

