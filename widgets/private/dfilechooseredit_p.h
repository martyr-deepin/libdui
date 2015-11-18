#ifndef DFILECHOOSEREDIT_P_H
#define DFILECHOOSEREDIT_P_H

#include "dlineedit_p.h"
#include "dobject.h"
#include "dobject_p.h"
#include "dfilechooseredit.h"
#include "dimagebutton.h"

DUI_BEGIN_NAMESPACE

class DFileChooserEditPrivate : DLineEditPrivate
{
    Q_DECLARE_PUBLIC(DFileChooserEdit)

public:
    DFileChooserEditPrivate(DFileChooserEdit *q);

    void init();

public:
    void _q_showFileChooserDialog();
};

DUI_END_NAMESPACE

#endif // DFILECHOOSEREDIT_P_H

