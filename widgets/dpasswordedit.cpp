#include "dpasswordedit.h"
#include "dthememanager.h"

#include <QHBoxLayout>
#include <QStyle>
#include <QDebug>
#include <QEvent>

DUI_BEGIN_NAMESPACE

DPasswordEdit::DPasswordEdit(QWidget *parent)
    : QFrame(parent),
      m_btn(this)
{
    D_THEME_INIT_WIDGET(DPasswordEdit, isEchoMode, isAlertMode);

    initInsideFrame();

    // default echo mode is password
    m_edit.setEchoMode(QLineEdit::Password);
    m_edit.installEventFilter(this);

    QHBoxLayout *layout = new QHBoxLayout(m_insideFrame);
    layout->addWidget(&m_edit);
    layout->addWidget(&m_btn);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setEchoMode(m_echo);

    connect(&m_btn, &DImageButton::clicked, [this]() -> void {setEchoMode(!m_echo);});
    connect(&m_edit, &QLineEdit::textChanged, this, &DPasswordEdit::textChanged);
}

void DPasswordEdit::setEchoMode(const bool isEcho)
{
    if (m_echo == isEcho) {
        return;
    }

    m_echo = isEcho;
    m_edit.setEchoMode(isEcho ? QLineEdit::Normal : QLineEdit::Password);
    emit echoModeChanged();
}

void DPasswordEdit::setAlertMode(const bool isAlert)
{
    if (m_alert == isAlert) {
        return;
    }

    m_alert = isAlert;
    emit alertModeChanged();
}

bool DPasswordEdit::eventFilter(QObject *o, QEvent *e)
{
    if (o == &m_edit) {
        if (e->type() == QEvent::FocusIn) {
            emit focusChanged(true);
        } else if (e->type() == QEvent::FocusOut) {
            emit focusChanged(false);
        }
    }

    return false;
}

//Bypassing the problem here
//qss can't draw box-shadow
void DPasswordEdit::initInsideFrame()
{
    m_insideFrame = new QFrame(this);
    m_insideFrame->raise();
    m_insideFrame->setObjectName("DEditInsideFrame");
    QHBoxLayout *insideLayout = new QHBoxLayout(this);
    insideLayout->setContentsMargins(0, 0, 0, 1);
    insideLayout->setSpacing(0);
    insideLayout->addWidget(m_insideFrame);
}

DUI_END_NAMESPACE
