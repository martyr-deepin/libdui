#include "dfilechooseredit.h"
#include "dthememanager.h"
#include "private/dfilechooseredit_p.h"

#include <QDebug>
#include <QFileDialog>
#include <QScreen>
#include <QGuiApplication>

DUI_BEGIN_NAMESPACE

DFileChooserEdit::DFileChooserEdit(QWidget *parent)
    : DLineEdit(*new DFileChooserEditPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(DFileChooserEdit);
    D_D(DFileChooserEdit);

    d->init();
}

DFileChooserEdit::DialogDisplayPosition DFileChooserEdit::dialogDisplayPosition() const
{
    D_DC(DFileChooserEdit);

    return d->dialogDisplayPosition;
}

void DFileChooserEdit::setDialogDisplayPosition(DFileChooserEdit::DialogDisplayPosition dialogDisplayPosition)
{
    D_D(DFileChooserEdit);

    d->dialogDisplayPosition = dialogDisplayPosition;
}

DFileChooserEditPrivate::DFileChooserEditPrivate(DFileChooserEdit *q)
    : DLineEditPrivate(q)
{
}

void DFileChooserEditPrivate::init()
{
    D_Q(DFileChooserEdit);

    q->setTextMargins(0, 0, 16, 0);
    q->setReadOnly(true);
    q->setIconVisible(true);
    q->connect(q, SIGNAL(iconClicked()), q, SLOT(_q_showFileChooserDialog()));
}

void DFileChooserEditPrivate::_q_showFileChooserDialog()
{
    D_Q(DFileChooserEdit);

    QFileDialog dialog(q);

    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);

    if(dialogDisplayPosition == DFileChooserEdit::CurrentMonitorCenter) {
        QPoint pos = QCursor::pos();

        for(QScreen *screen : qApp->screens()) {
            if(screen->geometry().contains(pos)) {
                QRect rect = dialog.geometry();
                rect.moveCenter(screen->geometry().center());
                dialog.move(rect.topLeft());
            }
        }
    }

    q->dialogOpened();
    q->dialogClosed(dialog.exec());

    if(!dialog.selectedFiles().isEmpty()) {
        const QString fileName = dialog.selectedFiles().first();

        q->setText(fileName);
        emit q->fileChoosed(fileName);
    }
}

DUI_END_NAMESPACE

#include "moc_dfilechooseredit.cpp"
