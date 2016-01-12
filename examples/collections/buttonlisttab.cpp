#include "buttonlisttab.h"
#include "dbuttonlist.h"
#include "doptionlist.h"
#include "doption.h"

#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QDebug>

DUI_USE_NAMESPACE

ButtonListTab::ButtonListTab(QWidget *parent) : QFrame(parent)
{
    initData();
    initUI();
    initConnect();
}

ButtonListTab::~ButtonListTab()
{

}

void ButtonListTab::initData() {
    m_buttons << "Button1" << "Button2" << "Button3";
    m_buttons << "Button4" << "Button5" << "Button6";
    m_buttons << "Button7" << "Button8" << "Button9";
}

void ButtonListTab::initUI() {
    DButtonList* buttonListGroup = new DButtonList(this);
    buttonListGroup->addButtons(m_buttons);
    buttonListGroup->setItemSize(200, 30);

    DOptionList *optionList = new DOptionList(this);
    for (int i = 0; i != 10; ++i)
    {
        DOption *option = new DOption;
        option->setName("aaaa");
        option->setValue("bbb");
        option->setIcon(":/images/dark/images/delete_multi_press.png");

        optionList->addOption(option);
    }
    optionList->setCurrentSelected(4);

    DOptionList *optionList2 = new DOptionList(this);
    for (int i = 0; i != 10; ++i)
    {
        DOption *option = new DOption;
        option->setName("aaaa");
        option->setValue("value-" + QString::number(i));
        option->layout()->setSpacing(0);

        optionList2->addOption(option);
    }
    optionList2->setCurrentSelected("value-4");

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(buttonListGroup);
    layout->addWidget(optionList);
    layout->addWidget(optionList2);
    layout->setContentsMargins(50, 50, 50, 50);
    setLayout(layout);
    buttonListGroup->checkButtonByIndex(2);
    buttonListGroup->addButton("1111");

    connect(buttonListGroup, SIGNAL(buttonMouseEntered(QString)),
            this, SLOT(handleEnter(QString)));

    connect(buttonListGroup, SIGNAL(buttonMouseLeaved(QString)),
            this, SLOT(handleLeave(QString)));

    buttonListGroup->clear();
    buttonListGroup->addButtons(m_buttons);
    buttonListGroup->checkButtonByIndex(4);
}

void ButtonListTab::handleEnter(QString text){
    qDebug() << "handleEnter" << text;
}

void ButtonListTab::handleLeave(QString text){
    qDebug() << "handleLeave" << text;
}

void ButtonListTab::initConnect(){

}
