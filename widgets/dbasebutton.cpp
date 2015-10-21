#include "dbasebutton.h"
#include "dthememanager.h"

DUI_USE_NAMESPACE

DBaseButton::DBaseButton(QWidget *parent) :
    QPushButton(parent)
{
    D_THEME_INIT_WIDGET(DBaseButton);

    initInsideFrame();
}

DBaseButton::DBaseButton(const QString &text, QWidget *parent) :
    QPushButton(text, parent)
{
    D_THEME_INIT_WIDGET(DBaseButton);

    initInsideFrame();
}

DBaseButton::DBaseButton(const QIcon &icon, const QString &text, QWidget *parent) :
    QPushButton(icon, text, parent)
{
    D_THEME_INIT_WIDGET(DBaseButton);

    initInsideFrame();
}

//Bypassing the problem here
//qss can't draw box-shadow
void DBaseButton::initInsideFrame()
{
    QFrame *insideFrame = new QFrame;
    insideFrame->raise();
    insideFrame->setAttribute(Qt::WA_TransparentForMouseEvents);
    insideFrame->setObjectName("ButtonInsideFrame");
    QHBoxLayout *insideLayout = new QHBoxLayout(this);
    insideLayout->setContentsMargins(0, 1, 0, 0);
    insideLayout->addWidget(insideFrame);
}
