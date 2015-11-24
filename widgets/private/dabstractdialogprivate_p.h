#ifndef DABSTRACTDIALOG_P_H
#define DABSTRACTDIALOG_P_H

#include "dobject_p.h"
#include "dabstractdialog.h"

class QBoxLayout;

DUI_BEGIN_NAMESPACE

class DAbstractDialogPrivate : public DObjectPrivate
{
public:
    DAbstractDialogPrivate(DAbstractDialog *qq);

private:
    QPoint dragPosition;
    int movableHeight = 30;

    void init();

    Q_DECLARE_PUBLIC(DAbstractDialog)
};

DUI_END_NAMESPACE

#endif // DABSTRACTDIALOG_P_H

