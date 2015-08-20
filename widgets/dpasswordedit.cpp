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
    D_THEME_INIT_WIDGET(DPasswordEdit);

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
    m_echo = isEcho;
    m_edit.setEchoMode(isEcho ? QLineEdit::Normal : QLineEdit::Password);

    // TODO theme
    D_THEME_INIT_WIDGET(DPasswordEdit);
}

void DPasswordEdit::setAlertMode(const bool isAlert)
{
    m_alert = isAlert;

    // TODO theme
    D_THEME_INIT_WIDGET(DPasswordEdit);
}

DUI_END_NAMESPACE
