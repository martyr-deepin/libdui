#include "buttongridtab.h"
#include "dbuttongrid.h"

#include <QHBoxLayout>
#include <QDebug>

DUI_USE_NAMESPACE

ButtonGridTab::ButtonGridTab(QWidget *parent) : QFrame(parent)
{
    initData();
    initUI();
    initConnect();
    setStyleSheet("background-color: rgba(52, 52, 52, 0.9)");
}

ButtonGridTab::~ButtonGridTab()
{

}

void ButtonGridTab::initData(){
    m_buttons << "Button1" << "Button2" << "Button3";
    m_buttons << "1ms" << "2ms" << "3ms";
    m_buttons << "aa" << "bb" << "cc" << "asassa";
}

void ButtonGridTab::initUI(){


    DButtonGrid* buttonGridGroup = new DButtonGrid(3, 4, this);
    buttonGridGroup->setItemSize(60, 40);
    buttonGridGroup->addButtons(m_buttons);
    buttonGridGroup->addButtons(m_buttons);
    buttonGridGroup->setShowGrid(false);
    connect(buttonGridGroup, SIGNAL(buttonChecked(QString)), this, SLOT(handleClicked(QString)));

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(buttonGridGroup);
    layout->setContentsMargins(50, 50, 50, 50);
    setLayout(layout);

    buttonGridGroup->checkButtonByIndex(2);
    buttonGridGroup->addButtons(m_buttons);
}


void ButtonGridTab::handleClicked(QString label){
    qDebug() << label << "clicked";
}

void ButtonGridTab::initConnect(){

}

