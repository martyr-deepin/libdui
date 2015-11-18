#include "dfilechooseredit.h"
#include "dthememanager.h"
#include "private/dfilechooseredit_p.h"

#include <QDebug>
#include <QFileDialog>

DUI_BEGIN_NAMESPACE

DFileChooserEdit::DFileChooserEdit(QWidget *parent)
    : DLineEdit(*new DFileChooserEditPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(DFileChooserEdit);
    D_D(DFileChooserEdit);

    d->init();
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

    const QString fileName = QFileDialog::getOpenFileName(q);

    q->setText(fileName);
    emit q->fileChoosed(fileName);
}

DUI_END_NAMESPACE

#include "moc_dfilechooseredit.cpp"
