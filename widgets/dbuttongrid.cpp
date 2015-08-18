#include "dbuttongrid.h"
#include "dthememanager.h"
#include <QButtonGroup>
#include <QHeaderView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

DUI_BEGIN_NAMESPACE


ImageButton::ImageButton(const QString &icon, const QString text,
                         bool isNameVisible, QWidget *parent):
    QPushButton(parent),
    m_icon(icon),
    m_text(text),
    m_isNameVisible(isNameVisible){
    setProperty("type", "ImageButton");
    initUI();
    initConnect();
}

void ImageButton::initUI(){
    m_iconLabel = new QLabel;
    m_iconLabel->setObjectName("IconLabel");
    m_iconLabel->setProperty("state", "normal");
    m_iconLabel->setPixmap(QPixmap(m_icon).scaled(m_iconLabel->size()));

    QVBoxLayout* mainlayout = new QVBoxLayout;
    mainlayout->addWidget(m_iconLabel);

    if (m_isNameVisible){
        m_textLabel = new QLabel;
        m_textLabel->setObjectName("TextLabel");
        m_textLabel->setAlignment(Qt::AlignCenter);
        m_textLabel->setProperty("state", "normal");
        m_textLabel->setText(m_text);
        mainlayout->addWidget(m_textLabel);
    }
    mainlayout->setSpacing(0);
    mainlayout->setContentsMargins(5, 5, 5, 5);
    setLayout(mainlayout);
}

void ImageButton::initConnect(){
    connect(this, SIGNAL(clicked(bool)), this, SLOT(handleChecked(bool)));
}

void ImageButton::handleChecked(bool checked){
    if (checked){
        m_iconLabel->setProperty("state","checked");
        if (m_textLabel){
            m_textLabel->setProperty("state","checked");
        }
    }else{
        m_iconLabel->setProperty("state","normal");
        if (m_textLabel){
            m_textLabel->setProperty("state","normal");
        }
    }
    updateChildWidgets();
}

void ImageButton::handleHover(bool hovered){

}

void ImageButton::updateChildWidgets(){
    m_iconLabel->style()->unpolish(m_iconLabel);
    m_iconLabel->style()->polish(m_iconLabel);
    m_iconLabel->update();
    if (m_textLabel){
        m_textLabel->style()->unpolish(m_textLabel);
        m_textLabel->style()->polish(m_textLabel);
        m_textLabel->update();
    }
}

void ImageButton::enterEvent(QEvent *event){
    if (m_iconLabel->property("state").isValid()){
        if (m_iconLabel->property("state").toString() == "checked"){

        }else{
             m_iconLabel->setProperty("state","hover");
        }
    }
    if (m_textLabel){
        if (m_textLabel->property("state").isValid()){
            if (m_textLabel->property("state").toString() == "checked"){

            }else{
                 m_textLabel->setProperty("state","hover");
            }
        }
    }
    updateChildWidgets();
    QPushButton::enterEvent(event);
}
void ImageButton::leaveEvent(QEvent *event){
    if (m_iconLabel->property("state").isValid()){
        if (m_iconLabel->property("state").toString() == "checked"){

        }else{
             m_iconLabel->setProperty("state","normal");
        }
    }
    if (m_textLabel){
        if (m_textLabel->property("state").isValid()){
            if (m_textLabel->property("state").toString() == "checked"){

            }else{
                 m_textLabel->setProperty("state","normal");
            }
        }
    }
    updateChildWidgets();
    QPushButton::leaveEvent(event);
}

void ImageButton::resizeEvent(QResizeEvent *event){
    m_iconLabel->setPixmap(QPixmap(m_icon).scaled(m_iconLabel->size()));
    if (m_textLabel){
        QFontMetrics fm = m_textLabel->fontMetrics();
        m_textLabel->setFixedHeight(fm.height() + 10);
    }
    QPushButton::resizeEvent(event);
}

ImageButton::~ImageButton(){

}


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
    m_columnWidth = width;
    m_rowHeight = height;
    for(int i = 0; i< rowCount(); i++){
        setRowHeight(i, height);
    }
    for (int j=0; j < columnCount(); j++){
        setColumnWidth(j, width);
    }

    for(int i= 0; i< m_buttonGroup->buttons().length(); i++){
        if (m_buttonGroup->buttons().at(i)->property("type").toString() == "ImageButton"){
            m_buttonGroup->buttons().at(i)->setFixedSize(width, height);
        }
    }

    setFixedSize(width * columnCount(), height* rowCount());
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
}

void DButtonGrid::addButtons(const QStringList &listLabels){
    int length = m_buttonLabels.length();
    int oldRowCount = rowCount();
    m_buttonLabels.append(listLabels);
    int _rowCount = 0;
    if (m_buttonLabels.length() % columnCount() == 0){
        _rowCount = m_buttonLabels.length()/columnCount();
    }else{
        _rowCount = m_buttonLabels.length()/columnCount() + 1;
    }
    for (int i = oldRowCount; i< _rowCount; i++){
        insertRow(i);
    }
    foreach (QString label, listLabels) {
        int index = listLabels.indexOf(label);
        addButton(label, length + index);
    }

    setItemUnChecked();
    setFixedSize(columnCount() * m_columnWidth, rowCount() * m_rowHeight);
}

void DButtonGrid::addImageButton(const QMap<QString, QString> &imageInfo,
                                 int index, bool isNameVisible){
    int _columnCount = columnCount();
    int row = index / _columnCount;
    int column = index % _columnCount;

    ImageButton* button = new ImageButton(imageInfo.value("url"), imageInfo.value("name"), isNameVisible);
    if (imageInfo.contains("key")){
        button->setProperty("key", imageInfo.value("key"));
    }
    button->setCheckable(true);
    m_buttonGroup->addButton(button, index);

    QFrame* buttonFrame = new QFrame(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(button, 0, Qt::AlignCenter);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    buttonFrame->setLayout(mainLayout);
    setCellWidget(row, column, buttonFrame);
}

void DButtonGrid::addImageButtons(const QList<QMap<QString, QString> > &imageInfos, bool isNameVisible){
    int length = m_imageButtonInfos.length();
    int oldRowCount = rowCount();
    m_imageButtonInfos.append(imageInfos);

    int _rowCount = 0;
    if (m_imageButtonInfos.length() % columnCount() == 0){
        _rowCount = m_imageButtonInfos.length()/columnCount();
    }else{
        _rowCount = m_imageButtonInfos.length()/columnCount() + 1;
    }

    for (int i = oldRowCount; i< _rowCount; i++){
        insertRow(i);
    }

    for (int i=0; i < imageInfos.count(); i++) {
        addImageButton(imageInfos.at(i), length + i, isNameVisible);
    }
    setItemUnChecked();
    setItemSize(m_columnWidth, m_rowHeight);
}


void DButtonGrid::setButtonChecked(int id){
   QPushButton* button = reinterpret_cast<QPushButton*>(m_buttonGroup->button(id));
   emit buttonCheckedIndexChanged(id);
   if (button->property("type").isValid() && button->property("type").toString() == "ImageButton"){
       if (button->property("key").isValid()){
           emit buttonChecked(button->property("key").toString());
       }
   }else{
       emit buttonChecked(button->text());
   }
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