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
    void init();
    QRect getParentGeometry() const;

    QPoint dragPosition;
    QColor backgroundColor;
    QColor borderColor;

    Q_DECLARE_PUBLIC(DAbstractDialog)
};

DUI_END_NAMESPACE

#endif // DABSTRACTDIALOG_P_H

