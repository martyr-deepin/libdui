#include "dsearchedit.h"
#include "dthememanager.h"

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPropertyAnimation>
#include <QDebug>
#include <QEvent>

DUI_USE_NAMESPACE

DSearchEdit::DSearchEdit(QWidget *parent)
    : QFrame(parent)
{
    D_THEME_INIT_WIDGET(DSearchEdit);

    m_btn = new DUI::DImageButton;
    m_edt = new QLineEdit;
    m_btn->setObjectName("Icon");
    m_edt->setObjectName("Edit");

    //setObjectName("DSearchEdit");
    setAutoFillBackground(true);
    //setStyleSheet("background-color:red;");

    m_size = QSize(m_btn->sizeHint().width() + m_edt->sizeHint().width(), qMax(m_btn->sizeHint().height(), m_edt->sizeHint().height()));
    setFixedSize(m_size);
    m_edt->setFixedWidth(0);

    //QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout *layout = new QHBoxLayout;
    //layout->addSpacerItem(spacer);
    layout->addStretch();
    layout->addWidget(m_btn);
    layout->addWidget(m_edt);
    layout->addStretch();
    //layout->addSpacerItem(spacer);
    layout->setSpacing(0);
    layout->setMargin(0);

    setLayout(layout);

    m_edt->installEventFilter(this);

    connect(m_edt, &QLineEdit::textChanged, this, &DSearchEdit::textChanged, Qt::DirectConnection);
    connect(m_edt, &QLineEdit::editingFinished, this, &DSearchEdit::editingFinished, Qt::DirectConnection);
}

const QString DSearchEdit::text() const
{
    return std::move(m_edt->text());
}

void DSearchEdit::mousePressEvent(QMouseEvent *)
{
    //m_edt.setFixedWidth(m_size.width() - m_btn.width());

    QPropertyAnimation *animation = new QPropertyAnimation(m_edt, "maximumWidth");
    animation->setStartValue(0);
    animation->setEndValue(m_size.width() - m_btn->width());
    animation->setDuration(animationDuration);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start();

    m_edt->show();
    m_edt->setFocus();
}

bool DSearchEdit::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_edt && e->type() == QEvent::FocusOut && m_edt->text().isEmpty())
    {
        //m_edt.setFixedWidth(0);

        QPropertyAnimation *animation = new QPropertyAnimation(m_edt, "maximumWidth");
        animation->setStartValue(m_edt->width());
        animation->setEndValue(0);
        animation->setDuration(animationDuration);
        animation->setEasingCurve(QEasingCurve::InCubic);
        animation->start();
    }

    return QFrame::eventFilter(o, e);
}
