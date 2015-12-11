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
protected:
    DDialogPrivate(DDialog *qq);

private:
    bool onButtonClickedClose = true;
    QIcon icon;
    QString title;
    QString message;
    Qt::TextFormat textFormat;

    QLabel* iconLabel;
    QLabel* messageLabel;
    QLabel* titleLabel;

    QPushButton* closeButton;
    QHBoxLayout *iconLayout;
    QVBoxLayout *contentLayout;
    QHBoxLayout *buttonLayout;
    const QScreen *targetScreen = nullptr;

    QList<QAbstractButton*> buttonList;
    QList<QWidget*> contentList;

    int clickedButtonIndex;

    void init();
    const QScreen *getScreen() const;

    void _q_onButtonClicked();
    void _q_updateLabelMaxWidth();

    Q_DECLARE_PUBLIC(DDialog)
};

DUI_END_NAMESPACE

#endif // DDIALOG_P_H

