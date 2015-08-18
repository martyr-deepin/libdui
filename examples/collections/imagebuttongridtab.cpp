#include "imagebuttongridtab.h"
#include "dbuttongrid.h"

#include <QHBoxLayout>
#include <QDebug>

DUI_USE_NAMESPACE

ImageButtonGridTab::ImageButtonGridTab(QWidget *parent) : QFrame(parent)
{
    initData();
    initUI();
    initConnect();
    setStyleSheet("background-color: rgba(52, 52, 52, 0.9)");
}

ImageButtonGridTab::~ImageButtonGridTab()
{

}

void ImageButtonGridTab::initData(){
    for(int i= 0; i<4; i++){
        QMap<QString, QString> imageInfo;
        imageInfo.insert("key", QString("image%1").arg(QString::number(i)));
        imageInfo.insert("name", QString("image%1").arg(QString::number(i)));
        imageInfo.insert("url", ":/images/wallpaper/1.jpg");
        m_imageInfos.append(imageInfo);
    }
}

void ImageButtonGridTab::initUI(){
    DButtonGrid* buttonGridGroup = new DButtonGrid(2, 2, this);
    buttonGridGroup->setItemSize(100, 80);
    buttonGridGroup->addImageButtons(m_imageInfos, true);
    buttonGridGroup->addImageButtons(m_imageInfos, false);
    connect(buttonGridGroup, SIGNAL(buttonChecked(QString)), this, SLOT(handleClicked(QString)));
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(buttonGridGroup, 0, Qt::AlignCenter);
    layout->setContentsMargins(10, 0, 0, 0);
    setLayout(layout);
    buttonGridGroup->checkButtonByIndex(2);
}


void ImageButtonGridTab::handleClicked(QString label){
    qDebug() << label << "clicked";
}

void ImageButtonGridTab::initConnect(){

}

