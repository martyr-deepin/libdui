#include "dpasswordedit.h"
#include "dthememanager.h"
#include "private/dpasswordedit_p.h"

#include <QDebug>

DUI_BEGIN_NAMESPACE

DPasswordEdit::DPasswordEdit(QWidget *parent)
    : DLineEdit(*new DPasswordEditPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(DPasswordEdit);
    D_D(DPasswordEdit);

    d->init();
}

bool DPasswordEdit::isEchoMode() const
{
    return echoMode() == Normal;
}

void DPasswordEdit::setEchoMode(QLineEdit::EchoMode mode)
{
    QLineEdit::setEchoMode(mode);

    setStyleSheet(styleSheet());
}

DPasswordEditPrivate::DPasswordEditPrivate(DPasswordEdit *q)
    : DLineEditPrivate(q)
{

}

void DPasswordEditPrivate::init()
{
    D_Q(DPasswordEdit);

    q->setEchoMode(q->Password);
    q->setTextMargins(0, 0, 16, 0);
    q->setIconVisible(true);

    q->connect(q, SIGNAL(iconClicked()), q, SLOT(_q_toggleEchoMode()));
}

void DPasswordEditPrivate::_q_toggleEchoMode()
{
    D_Q(DPasswordEdit);

    if (q->isEchoMode())
        q->setEchoMode(q->Password);
    else
        q->setEchoMode(q->Normal);
}

DUI_END_NAMESPACE

#include "moc_dpasswordedit.cpp"

