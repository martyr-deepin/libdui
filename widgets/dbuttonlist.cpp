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

void DButtonList::addButton(const QString &label){
    QPushButton* button = new QPushButton(label, this);
    button->setFixedSize(gridSize());
    button->setCheckable(true);
    m_buttonGroup->addButton(button);
    QListWidgetItem* item = new QListWidgetItem(this);
    addItem(item);
    setItemWidget(item, button);
}


void DButtonList::addButtons(const QStringList &listLabels){
    foreach (QString label, listLabels) {
        addButton(label);
    }
}

void DButtonList::setButtonChecked(int id){
   QAbstractButton * button = m_buttonGroup->button(id);
   button->setChecked(true);

   emit buttonChecked(button->text());
}

DUI_END_NAMESPACE
