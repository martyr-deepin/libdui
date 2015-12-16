#ifndef DIPV4LINEEDIT_P_H
#define DIPV4LINEEDIT_P_H

#include "dlineedit_p.h"
#include "dipv4lineedit.h"

DUI_BEGIN_NAMESPACE

class DIpv4LineEditPrivate : public DLineEditPrivate
{
    DIpv4LineEditPrivate(DIpv4LineEdit *parent);

    void init();

    QLabel *getLabel();
    QLineEdit *getEdit();

    void _q_updateLineEditText();
    void _q_setIpLineEditText(const QString &text);

    QList<QLineEdit*> editList;
    QWidget *editMainWidget;

    D_DECLARE_PUBLIC(DIpv4LineEdit)
};

DUI_END_NAMESPACE

#endif // DIPV4LINEEDIT_P_H

