#include "dbuttonlist.h"
#include "dthememanager.h"
#include "dconstants.h"
#include <QListWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QListWidgetItem>

DUI_BEGIN_NAMESPACE

DButtonList::DButtonList(QWidget *parent) : QListWidget(parent)
{
    D_THEME_INIT_WIDGET(DButtonList);

    setSelectionMode(DButtonList::NoSelection);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(ScrollPerItem);
    setResizeMode(Adjust);
    setItemSize(200, BUTTON_HEIGHT);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);

    initConnect();
}


DButtonList::~DButtonList()
{

}

void DButtonList::initConnect(){
    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setButtonChecked(int)));
}

void DButtonList::setItemWidth(int width){
    setGridSize(QSize(width, gridSize().height()));
    setFixedWidth(gridSize().width());
}

void DButtonList::setItemHeight(int height){
    setGridSize(QSize(gridSize().width(), height));
}

void DButtonList::setItemSize(int width, int height){
    setItemSize(QSize(width, height));
}

void DButtonList::setItemSize(QSize size){
    setGridSize(size);
    setFixedWidth(gridSize().width());
}

void DButtonList::addButton(const QString &label, int index){
    QPushButton* button = new QPushButton(label, this);
    button->setFixedSize(gridSize());
    button->setCheckable(true);
    m_buttonGroup->addButton(button, index);
    QListWidgetItem* item = new QListWidgetItem(this);
    addItem(item);
    setItemWidget(item, button);
}


void DButtonList::addButtons(const QStringList &listLabels){
    for(int i= 0; i< listLabels.length(); i++) {
        addButton(listLabels.at(i), i);
    }
}

void DButtonList::setButtonChecked(int id){
   QPushButton* button = reinterpret_cast<QPushButton*>(m_buttonGroup->button(id));
   button->setChecked(true);
   emit buttonCheckedIndexChanged(id);
   emit buttonChecked(button->text());
}

void DButtonList::checkButtonByIndex(int index){
    QPushButton* button = reinterpret_cast<QPushButton*>(m_buttonGroup->button(index));
    button->click();
}

DUI_END_NAMESPACE
