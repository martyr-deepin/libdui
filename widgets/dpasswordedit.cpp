#include "dpasswordedit.h"
#include "dthememanager.h"

#include <QHBoxLayout>

DUI_BEGIN_NAMESPACE

DPasswordEdit::DPasswordEdit(QWidget *parent)
    : QWidget(parent),
      m_btn(this)
{
    D_THEME_INIT_WIDGET(DPasswordEdit);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(&m_edit);
    layout->addWidget(&m_btn);
    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    m_edit.setEchoMode(QLineEdit::Password);
    m_btn.setCheckable(true);

    connect(&m_btn, &DImageButton::stateChanged, [this] () -> void {m_edit.setEchoMode(m_btn.isChecked() ? QLineEdit::Normal : QLineEdit::Password);});
}

DUI_END_NAMESPACE
