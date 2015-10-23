#include <QHBoxLayout>
#include "dlineedit.h"
#include "dthememanager.h"

DUI_USE_NAMESPACE

DLineEdit::DLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    D_THEME_INIT_WIDGET(DLineEdit, alert);

    initInsideFrame();
}

void DLineEdit::setAlert(bool isAlert)
{
    if (m_isAlert == isAlert)
        return;
    m_isAlert = isAlert;
    emit alertChanged();
}

//Bypassing the problem here
//qss can't draw box-shadow
void DLineEdit::initInsideFrame()
{
    QFrame *insideFrame = new QFrame;
    insideFrame->raise();
    insideFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
    insideFrame->setObjectName("LineEditInsideFrame");
    QHBoxLayout *insideLayout = new QHBoxLayout(this);
    insideLayout->setContentsMargins(0, 0, 0, 1);
    insideLayout->addWidget(insideFrame);
}

