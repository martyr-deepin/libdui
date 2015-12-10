#ifndef DINPUTDIALOG_P_H
#define DINPUTDIALOG_P_H

#include "dinputdialog.h"
#include "ddialog_p.h"

DUI_BEGIN_NAMESPACE

class DLabel;
class DLineEdit;
class DSpinBox;
class DDoubleSpinBox;
class DComboBox;
class DInputDialogPrivate : public DDialogPrivate
{
    DInputDialogPrivate(DInputDialog *qq);

    QAbstractButton *cancelButton = nullptr;
    QAbstractButton *okButton = nullptr;
    DLabel *label = nullptr;
    DLineEdit *lineEdit = nullptr;
    DSpinBox* spinBox = nullptr;
    DDoubleSpinBox *doubleSpinBox = nullptr;
    DComboBox *comboBox = nullptr;

    DInputDialog::InputMode inputMode;

    void init();

    D_DECLARE_PUBLIC(DInputDialog)
};

DUI_END_NAMESPACE

#endif // DINPUTDIALOG_P_H

