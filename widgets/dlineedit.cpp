#include "dlineedit.h"
#include "dthememanager.h"
#include "private/dlineedit_p.h"

#include <QHBoxLayout>

DUI_USE_NAMESPACE

DLineEdit::DLineEdit(QWidget *parent)
    : QLineEdit(parent),
      DObject(*new DLineEditPrivate(this))
{
    D_THEME_INIT_WIDGET(DLineEdit, alert);
}

void DLineEdit::setAlert(bool isAlert)
{
    Q_D(DLineEdit);

    if (isAlert == d->m_isAlert)
        return;

    d->m_isAlert = isAlert;
    emit alertChanged();
}

bool DLineEdit::isAlert() const
{
    Q_D(const DLineEdit);

    return d->m_isAlert;
}

void DLineEdit::focusInEvent(QFocusEvent *e)
{
    emit focusChanged(true);
    QLineEdit::focusInEvent(e);
}

void DLineEdit::focusOutEvent(QFocusEvent *e)
{
    emit focusChanged(false);
    QLineEdit::focusOutEvent(e);
}

DUI::DLineEditPrivate::DLineEditPrivate(DUI::DLineEdit *q)
    : DObjectPrivate(q)
{
    QFrame *insideFrame = new QFrame;
    insideFrame->raise();
    insideFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
    insideFrame->setObjectName("LineEditInsideFrame");

    m_centeralLayout = new QHBoxLayout;
    m_centeralLayout->setContentsMargins(0, 0, 0, 1);
    m_centeralLayout->addWidget(insideFrame);

    q->setLayout(m_centeralLayout);
}
