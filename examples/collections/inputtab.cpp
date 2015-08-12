#include "inputtab.h"
#include "dshortcutedit.h"

#include <QPixmap>

InputTab::InputTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("InputTab{background-color: #252627;}");
    setFocusPolicy(Qt::ClickFocus);

    DUI::DPasswordEdit *pwdEdit = new DUI::DPasswordEdit(this);
    pwdEdit->setNormalIcon(QPixmap(":/images/button.png"));
    pwdEdit->setHoverIcon(QPixmap(":/images/buttonHover.png"));
    pwdEdit->setShowPasswordIcon(QPixmap(":/images/buttonChecked.png"));
    pwdEdit->setPassword("password");
    pwdEdit->move(20, 20);

    DUI::DSearchEdit *searchEdit = new DUI::DSearchEdit(this);
    searchEdit->setSearchIcon(QPixmap(":/images/button.png"));
    searchEdit->move(20, 50);

    DUI::DLineEdit *lineEdit = new DUI::DLineEdit(this);
    lineEdit->setText("LineEdit");
    lineEdit->move(20, 80);

    DUI::DShortcutEdit *shortcutEdit = new DUI::DShortcutEdit(this);
    shortcutEdit->move(20, 110);
}
