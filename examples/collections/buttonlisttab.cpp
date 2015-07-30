#include "buttonlisttab.h"
#include "dbuttonlist.h"

#include <QHBoxLayout>
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

void ButtonListTab::initData(){
    m_buttons << "Button1" << "Button2" << "Button3";
}

void ButtonListTab::initUI(){


    DButtonList* buttonListGroup = new DButtonList(this);

    buttonListGroup->addButtons(m_buttons);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(buttonListGroup);
    layout->setContentsMargins(50, 50, 50, 50);
    setLayout(layout);

    buttonListGroup->addButtons(m_buttons);
    buttonListGroup->addButtons(m_buttons);
    buttonListGroup->addButtons(m_buttons);
}


void ButtonListTab::initConnect(){

}
