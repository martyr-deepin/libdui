#include "inputtab.h"
#include "dshortcutedit.h"
#include "dfilechooseredit.h"
#include "dipv4lineedit.h"
#include "dspinbox.h"

#include <QPixmap>
#include <QDebug>

InputTab::InputTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("InputTab{background-color: #252627;}");
    setFocusPolicy(Qt::ClickFocus);

    DUI::DPasswordEdit *pwdEdit = new DUI::DPasswordEdit(this);
    pwdEdit->setText("password");
    pwdEdit->move(20, 20);

    DUI::DPasswordEdit *pwdEdit2 = new DUI::DPasswordEdit(this);
    pwdEdit2->setText("password");
    pwdEdit2->setEchoMode(DUI::DPasswordEdit::Normal);
    pwdEdit2->setAlert(true);
    pwdEdit2->move(20, 50);
    connect(pwdEdit2, &DUI::DPasswordEdit::focusChanged, [](bool focus) {qDebug() << "focus: " << focus;});
    connect(pwdEdit2, &DUI::DPasswordEdit::textChanged, [](const QString &text) {qDebug() << "text: " << text;});

    DUI::DSearchEdit *searchEdit = new DUI::DSearchEdit(this);
    //searchEdit->setSearchIcon(":/images/button.png");
    //searchEdit->setFixedWidth(300);
    searchEdit->move(20, 120);
    searchEdit->setPlaceHolder("Tes");

    DUI::DLineEdit *lineEdit = new DUI::DLineEdit(this);
    lineEdit->setText("LineEdit");
    lineEdit->move(20, 180);
//    lineEdit->setAlert(true);
//    lineEdit->setFixedSize(200, 30);
    connect(lineEdit, &DUI::DLineEdit::focusChanged, [](bool focus) {qDebug() << "focus: " << focus;});

    DUI::DFileChooserEdit *fileChooser = new DUI::DFileChooserEdit(this);
    fileChooser->move(150, 180);
    fileChooser->setDialogDisplayPosition(DUI::DFileChooserEdit::CurrentMonitorCenter);

    DUI::DLineEdit *lineEditAlert = new DUI::DLineEdit(this);
    lineEditAlert->setText("AlertLineEdit");
    lineEditAlert->setAlert(true);
    lineEditAlert->setFixedSize(200, 30);
    lineEditAlert->move(20, 230);
    lineEditAlert->setValidator(new QRegExpValidator(QRegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){0,3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)?")));

    DUI::DShortcutEdit *shortcutEdit = new DUI::DShortcutEdit(this);
    shortcutEdit->move(20, 300);

    DUI::DIpv4LineEdit *ipv4 = new DUI::DIpv4LineEdit(this);

    ipv4->move(300, 20);

    connect(ipv4, &DUI::DIpv4LineEdit::textChanged, this, [this, ipv4](const QString &text) {
        qDebug() << "text changed:" <<text << ipv4->text();
    });

    ipv4->setText("192.168.31.55");

    DUI::DSpinBox *spinbox = new DUI::DSpinBox(this);

    spinbox->resize(100, 22);

    spinbox->move(300, 50);
}
