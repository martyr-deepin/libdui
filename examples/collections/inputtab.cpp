#include "inputtab.h"

#include <QPixmap>

InputTab::InputTab(QWidget *parent) : QWidget(parent)
{
    DUI::DPasswordEdit *pwdEdit = new DUI::DPasswordEdit(this);
    pwdEdit->setNormalIcon(QPixmap(":/images/button.png"));
    pwdEdit->setHoverIcon(QPixmap(":/images/buttonHover.png"));
    pwdEdit->setShowPasswordIcon(QPixmap(":/images/buttonChecked.png"));
    pwdEdit->setPassword("password");
    pwdEdit->move(20, 20);

    DUI::DSearchEdit *searchEdit = new DUI::DSearchEdit(this);
    searchEdit->setSearchIcon(QPixmap(":/images/button.png"));
    searchEdit->move(20, 50);
}
