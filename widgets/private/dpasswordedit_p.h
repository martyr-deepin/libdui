#ifndef DPASSWORDEDIT_P_H
#define DPASSWORDEDIT_P_H

#include "dlineedit_p.h"
#include "dpasswordedit.h"

DUI_BEGIN_NAMESPACE

class DPasswordEditPrivate : DLineEditPrivate
{
public:
    DPasswordEditPrivate(DPasswordEdit *q);

    void init();

    void _q_toggleEchoMode();

protected:
    Q_DECLARE_PUBLIC(DPasswordEdit)
};

DUI_END_NAMESPACE

#endif // DPASSWORDEDIT_P_H

