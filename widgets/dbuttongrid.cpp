#include "dbuttongrid.h"
#include "dthememanager.h"
#include <QButtonGroup>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QPushButton>

DUI_BEGIN_NAMESPACE

DButtonGrid::DButtonGrid(QWidget *parent) : QTableWidget(parent)
{
    init();
}

DButtonGrid::DButtonGrid(int rows, int columns, QWidget *parent):
    QTableWidget(rows, columns, parent){
    init();
}

void DButtonGrid::init(){
    D_THEME_INIT_WIDGET(DButtonGrid);
    setAttribute(Qt::WA_TranslucentBackground);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setEditTriggers(NoEditTriggers);
    setDragDropMode(NoDragDrop);
    setSelectionMode(NoSelection);
    setAcceptDrops(false);
    setDragEnabled(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setShowGrid(false);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);
    initConnect();
}

void DButtonGrid::initConnect(){
    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setButtonChecked(int)));
}

void DButtonGrid::setItemSize(int width, int height){
    for(int i = 0; i< rowCount(); i++){
        setRowHeight(i, height);
    }
    for (int j=0; j < columnCount(); j++){
        setColumnWidth(j, width);
    }
}

void DButtonGrid::addButton(const QString &label, int index){
    int _columnCount = columnCount();
    int row = index / _columnCount;
    int column = index % _columnCount;

    QFontMetrics fm = fontMetrics();
    int width = fm.width(label);
    QPushButton* button = new QPushButton(label, this);
    button->setFixedWidth(width + 20);
    button->setFixedHeight(fm.height() + 10);
    button->setCheckable(true);
    m_buttonGroup->addButton(button, index);

    QFrame* buttonFrame = new QFrame(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(button, 0, Qt::AlignHCenter);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    buttonFrame->setLayout(mainLayout);

    setCellWidget(row, column, buttonFrame);

    setFixedSize(columnCount() * m_columnWidth, rowCount() * m_rowHeight);
}


void DButtonGrid::addButtons(const QStringList &listLabels){
    foreach (QString label, listLabels) {
        int index = listLabels.indexOf(label);
        addButton(label, index);
    }
    setItemUnChecked();
}

void DButtonGrid::setButtonChecked(int id){
   QPushButton* button = reinterpret_cast<QPushButton*>(m_buttonGroup->button(id));
   button->setChecked(true);
   emit buttonCheckedIndexChanged(id);
   emit buttonChecked(button->text());
}

void DButtonGrid::checkButtonByIndex(int index){
    QPushButton* button = reinterpret_cast<QPushButton*>(m_buttonGroup->button(index));
    button->click();
}

void DButtonGrid::setItemUnChecked(){
    for(int i = 0; i< rowCount(); i++){
        for (int j=0; j < columnCount(); j++){
            if (item(i, j)){
                item(i, j)->setFlags(Qt::NoItemFlags);
            }else{
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setFlags(Qt::NoItemFlags);
                setItem(i, j, item);
            }
        }
    }
}

DButtonGrid::~DButtonGrid()
{

}

DUI_END_NAMESPACE
