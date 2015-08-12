#include "comboboxtab.h"
#include <QLineEdit>

ComboBoxTab::ComboBoxTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("ComboBoxTab{background-color: #252627;}");

    ////////////////////////////////////////////////Font ComboBox
    DFontComboBox *fcb = new DFontComboBox(this);
    fcb->setFixedSize(200, DUI::BUTTON_HEIGHT);
    fcb->move(30, 100);
    for (int i = 0; i < 50; i ++){
        fcb->addFontName(QString::number(i));
    }
    connect(fcb, &DFontComboBox::currentFontNameChange, [=](QString name){
        qWarning() << "Select font name: " << name;
    });

    /////////////////////////////////////////////Color ComboBox
    DColorComboBox *colorcb = new DColorComboBox(this);
    colorcb->setFixedSize(200, DUI::BUTTON_HEIGHT);
    colorcb->move(230, 100);
    for (int i = 0; i < 10; i ++){
        colorcb->addData(QString("#%1%2%3%4FF").arg(i).arg(i).arg(i).arg(i), QString::number(i));//support RRGGBB or AARRGGBB or color-name
    }
    connect(colorcb, &DColorComboBox::currentColorChange, [=](QColor color){
        qWarning() << "========+++++++++" << color;
    });

    ///////////////////////////////////////////////Normal ComboBox
    simpleBox = new DComboBox(this);
    simpleBox->setFixedSize(200, DUI::BUTTON_HEIGHT);
    simpleBox->move(430, 100);

    QStringList simpleList;
    for (int i = 0; i < 20; i ++){
        simpleList << QString::number(i);
    }
    simpleBox->addItems(simpleList);

}


