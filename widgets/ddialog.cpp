#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "ddialog.h"
#include "dthememanager.h"
#include "private/ddialog_p.h"

DUI_BEGIN_NAMESPACE

DDialogPrivate::DDialogPrivate(DDialog *qq) :
    DAbstractDialogPrivate(qq)
{

}

void DDialogPrivate::init()
{
    D_Q(DDialog);

    closeButton = new QPushButton(q);

    closeButton->setObjectName("CloseButton");
    closeButton->setFixedSize(25, 25);
    closeButton->setAttribute(Qt::WA_NoMousePropagation);
    messageLabelMaxWidth = qApp->desktop()->availableGeometry().width() / 2 -
                100 - 2 * closeButton->width();
}

DDialog::DDialog(QWidget *parent) :
    DAbstractDialog(*new DDialogPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(dialogs/DDialog);

    d_func()->init();
}

void DDialog::initUI(const QString &icon,
                     const QString &message,
                     const QString &tipMessage,
                     const QStringList &buttonKeys,
                     const QStringList &buttonTexts){
    D_D(DDialog);

    d->icon = icon;
    d->message = message;
    d->tipMessage = tipMessage;
    d->buttonKeys = buttonKeys;
    d->buttonTexts = buttonTexts;

    QFrame* contentFrame = new QFrame;
    contentFrame->setObjectName("ContentFrame");

    d->iconLabel = new QLabel;
    d->iconLabel->setFixedSize(48, 48);
    setIcon(d->icon);

    d->messageLabel = new QLabel;
    d->messageLabel->setObjectName("MessageLabel");
    setMessage(d->message);

    d->tipMessageLabel = new QLabel;
    d->tipMessageLabel->setObjectName("TipMessageLabel");
    setTipMessage(d->tipMessage);

    d->buttonGroup = new QButtonGroup;
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    foreach (QString label, d->buttonKeys) {
        int index = d->buttonKeys.indexOf(label);
        QPushButton* button = new QPushButton(label);
        button->setObjectName("ActionButton");
        button->setAttribute(Qt::WA_NoMousePropagation);
        button->setFixedHeight(28);
        d->buttonGroup->addButton(button, index);
        buttonLayout->addWidget(button);
        if (index < d->buttonKeys.length() - 1){
            QLabel* label = new QLabel;
            label->setObjectName("VLine");
            label->setFixedWidth(1);
            buttonLayout->addWidget(label);
        }
    }

    setButtonTexts(d->buttonTexts);
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* iconLayout = new QVBoxLayout;
    iconLayout->addWidget(d->iconLabel, Qt::AlignCenter);
    iconLayout->setContentsMargins(26, 22, 26, 22);

    d->messageLayout = new QVBoxLayout;
    d->messageLayout->addWidget(d->messageLabel);
    d->messageLayout->addWidget(d->tipMessageLabel);
    d->messageLayout->addStretch();
    d->messageLayout->setContentsMargins(5, d->closeButton->height(), d->closeButton->width(), 0);

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addLayout(iconLayout);
    topLayout->addLayout(d->messageLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    contentFrame->setLayout(mainLayout);

    QHBoxLayout* contentlayout = new QHBoxLayout;
    contentlayout->addWidget(contentFrame);
    contentlayout->setContentsMargins(5, 5, 5, 5);
    setLayout(contentlayout);

    resize(d->defaultWidth, d->defaultHeight);
    initConnect();
}


void DDialog::initConnect()
{
    D_DC(DDialog);

    connect(d->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(handleButtonsClicked(int)));
    connect(d->closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

QButtonGroup* DDialog::getButtonsGroup() const
{
    D_DC(DDialog);

    return d->buttonGroup;
}

QVBoxLayout* DDialog::getMessageLayout() const
{
    D_DC(DDialog);

    return d->messageLayout;
}

QString DDialog::getIcon() const
{
    D_DC(DDialog);

    return d->icon;
}

void DDialog::setIcon(const QString &icon)
{
    D_D(DDialog);

    d->icon = icon;
    d->iconLabel->setPixmap(QPixmap(d->icon).scaled(d->iconLabel->size()));
}

QString DDialog::getMessage() const
{
    D_DC(DDialog);

    return d->message;
}

void DDialog::setMessage(const QString &message)
{
    D_D(DDialog);

    d->message = message;

    QFontMetrics fm = fontMetrics();
    if (fm.width(d->message) > d->messageLabelMaxWidth){
        QString text = fm.elidedText(d->message, Qt::ElideRight, d->messageLabelMaxWidth);
        d->messageLabel->setText(text);
    }else{
        d->messageLabel->setText(d->message);
    }
    d->messageLabel->resize(fm.width(d->messageLabel->text()), height());
}

QString DDialog::getTipMessage() const
{
    D_DC(DDialog);

    return d->tipMessage;
}

void DDialog::setTipMessage(const QString &tipMessage)
{
    D_D(DDialog);

    d->tipMessage = tipMessage;

    QFontMetrics fm = fontMetrics();
    if (fm.width(d->tipMessage) > d->messageLabelMaxWidth){
        QString text = fm.elidedText(d->tipMessage, Qt::ElideRight, d->messageLabelMaxWidth);
        d->tipMessageLabel->setText(text);
    }else{
        d->tipMessageLabel->setText(d->tipMessage);
    }
    d->tipMessageLabel->resize(fm.width(d->messageLabel->text()), height());
}

QStringList DDialog::getButtons() const
{
    D_DC(DDialog);

    return d->buttonKeys;
}

void DDialog::setButtons(const QStringList &buttons)
{
    D_D(DDialog);

    d->buttonKeys = buttons;
}

QStringList DDialog::getButtonTexts() const
{
    D_DC(DDialog);

    return d->buttonTexts;
}

void DDialog::setButtonTexts(const QStringList& buttonTexts)
{
    D_D(DDialog);

    if (buttonTexts.length() != d->buttonKeys.length()){
        return;
    }
    d->buttonTexts = buttonTexts;
    for (int i = 0; i < d->buttonGroup->buttons().length(); i++) {
        QPushButton* button = reinterpret_cast<QPushButton*>(d->buttonGroup->buttons().at(i));
        button->setText(d->buttonTexts.at(i));
    }
}

void DDialog::handleButtonsClicked(int id)
{
    D_DC(DDialog);

    close();
    int index = d->buttonGroup->buttons().indexOf(d->buttonGroup->button(id));
    if (d->buttonKeys.length() > index){
        QString key = d->buttonKeys.at(index);
        emit buttonClicked(key);
        emit buttonClicked(index);
    }
}

void DDialog::handleKeyEnter()
{

}

void DDialog::closeEvent(QCloseEvent *event)
{
    emit aboutToClose();
    DAbstractDialog::closeEvent(event);
    emit closed();
}


void DDialog::resizeEvent(QResizeEvent *event)
{
    D_D(DDialog);

    d->closeButton->move(width() - d->closeButton->width() - 4, 4);
    d->closeButton->raise();
    moveCenter();
    DAbstractDialog::resizeEvent(event);
}

DUI_END_NAMESPACE
