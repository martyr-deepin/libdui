#include "comboboxtab.h"

ComboBoxTab::ComboBoxTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("ComboBoxTab{background-color: #252627;}");
    QStringList tl;
    for (int i = 0; i < 20; i ++){
        tl.append(QString::number(i));
    }
    DComboBox *cb = new DComboBox(this);
    cb->setFixedSize(300, DUI::BUTTON_HEIGHT);
    cb->addItems(tl);
    cb->move(100, 200);
}

