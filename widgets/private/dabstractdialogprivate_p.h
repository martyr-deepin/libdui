#ifndef DABSTRACTDIALOG_P_H
#define DABSTRACTDIALOG_P_H

#include "dobject_p.h"
#include "dabstractdialog.h"

class QBoxLayout;

DUI_BEGIN_NAMESPACE

class DAbstractDialogPrivate : public DObjectPrivate
{
protected:
    DAbstractDialogPrivate(DAbstractDialog *qq);

    QRect getParentGeometry() const;

private:
    void init();

    bool mouseMoved = false;
    /// 记录是否收到过鼠标移动事件.
    ///
    QPoint dragPosition;
    QColor backgroundColor;
    QColor borderColor;
    DAbstractDialog::DisplayPostion displayPostion;

    Q_DECLARE_PUBLIC(DAbstractDialog)
};

DUI_END_NAMESPACE

#endif // DABSTRACTDIALOG_P_H

