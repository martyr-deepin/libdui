#ifndef DDIALOG_P_H
#define DDIALOG_P_H

#include "ddialog.h"
#include "dabstractdialogprivate_p.h"

DUI_BEGIN_NAMESPACE

class DDialogPrivate : public DAbstractDialogPrivate
{
    DDialogPrivate(DDialog *qq);

    QString icon;
    QString message;
    QString tipMessage;
    QStringList buttonKeys;
    QStringList buttonTexts;
    int defaultWidth = 380;
    int defaultHeight = 120;

    QLabel* iconLabel;
    QLabel* messageLabel;
    QLabel* tipMessageLabel;
    QButtonGroup* buttonGroup;

    QVBoxLayout* messageLayout;
    int messageLabelMaxWidth;
    QPushButton* closeButton;

    void init();

    Q_DECLARE_PUBLIC(DDialog)
};

DUI_END_NAMESPACE

#endif // DDIALOG_P_H

