#include "dpasswordedit.h"
#include "dthememanager.h"

#include <QHBoxLayout>
#include <QStyle>
#include <QDebug>

DUI_BEGIN_NAMESPACE

DPasswordEdit::DPasswordEdit(QWidget *parent)
    : QFrame(parent),
      m_btn(this)
{
    D_THEME_INIT_WIDGET(DPasswordEdit, isEchoMode, isAlertMode);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(&m_edit);
    layout->addWidget(&m_btn);
    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    setEchoMode(m_echo);

    connect(&m_btn, &DImageButton::clicked, [this] () -> void {setEchoMode(!m_echo);});
    connect(&m_edit, &QLineEdit::textChanged, this, &DPasswordEdit::textChanged);
}

void DPasswordEdit::setEchoMode(const bool isEcho)
{
    if (m_echo == isEcho)
        return;

    m_echo = isEcho;
    m_edit.setEchoMode(isEcho ? QLineEdit::Normal : QLineEdit::Password);
    emit echoModeChanged();
}

void DPasswordEdit::setAlertMode(const bool isAlert)
{
    if (m_alert == isAlert)
        return;

    m_alert = isAlert;
    emit alertModeChanged();
}

DUI_END_NAMESPACE
