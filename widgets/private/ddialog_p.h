#ifndef DDIALOG_P_H
#define DDIALOG_P_H

#include "ddialog.h"
#include "dabstractdialogprivate_p.h"

class QHBoxLayout;

DUI_BEGIN_NAMESPACE

class DVBoxWidget;
class DHBoxWidget;
class DDialogPrivate : public DAbstractDialogPrivate
{
    DDialogPrivate(DDialog *qq);

    QIcon icon;
    QString title;
    QString message;
    Qt::TextFormat textFormat;

    QLabel* iconLabel;
    QLabel* messageLabel;
    QLabel* titleLabel;

    QPushButton* closeButton;
    DVBoxWidget *boxWidget;
    QHBoxLayout *iconLayout;
    QHBoxLayout *buttonLayout;

    QList<QAbstractButton*> buttonList;
    QList<QWidget*> contentList;

    int clickedButtonIndex;

    void init();
    void _q_onButtonClicked();

    Q_DECLARE_PUBLIC(DDialog)
};

DUI_END_NAMESPACE

#endif // DDIALOG_P_H

