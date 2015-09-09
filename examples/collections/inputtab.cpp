#include "inputtab.h"
#include "dshortcutedit.h"

#include <QPixmap>
#include <QDebug>

InputTab::InputTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("InputTab{background-color: #252627;}");
    setFocusPolicy(Qt::ClickFocus);

    DUI::DPasswordEdit *pwdEdit = new DUI::DPasswordEdit(this);
    pwdEdit->setPassword("password");
    pwdEdit->move(20, 20);

    DUI::DPasswordEdit *pwdEdit2 = new DUI::DPasswordEdit(this);
    pwdEdit2->setPassword("password");
    pwdEdit2->setEchoMode(true);
    pwdEdit2->setAlertMode(true);
    pwdEdit2->move(20, 50);

    DUI::DSearchEdit *searchEdit = new DUI::DSearchEdit(this);
    //searchEdit->setSearchIcon(":/images/button.png");
    //searchEdit->setFixedWidth(300);
    searchEdit->move(20, 80);

    DUI::DLineEdit *lineEdit = new DUI::DLineEdit(this);
    lineEdit->setText("LineEdit");
    lineEdit->move(20, 110);

    DUI::DLineEdit *lineEditAlert = new DUI::DLineEdit(this);
    lineEditAlert->setText("AlertLineEdit");
    lineEditAlert->setAlert(true);
    lineEditAlert->move(150, 110);

    DUI::DShortcutEdit *shortcutEdit = new DUI::DShortcutEdit(this);
    shortcutEdit->move(20, 140);
}
