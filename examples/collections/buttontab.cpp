#include "buttontab.h"
#include "QDebug"

ButtonTab::ButtonTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("ButtonTab{background-color: #252627;}");

    DArrowButton * arrowButton = new DArrowButton(this);
    arrowButton->setArrowDirection(DArrowButton::ArrowDown);
    arrowButton->move(5, 5);

    //////////////////////////////////////////////////////////////--DTextButton
    DTextButton *textButton = new DTextButton("Test Text", this);
    textButton->move(5, 40);
    
    DTextButton *textComplexButton = new DTextButton("Checked Button", this);
    textComplexButton->setCheckable(true);
    textComplexButton->setChecked(true);
    textComplexButton->move(5, 75);

    //////////////////////////////////////////////////////////////--DTextButton

    DImageButton *imageButton = new DImageButton(":/images/button.png", ":/images/buttonHover.png", ":/images/buttonPress.png", this);
    imageButton->move(5, 100);
    imageButton->setChecked(true);

    DImageButton *imageButton2 = new DImageButton(this);
    imageButton2->setNormalPic(QPixmap(":/images/buttonHover.png"));
    imageButton2->move(35, 100);

    DImageButton *checkableImageButton = new DImageButton(":/images/button.png", ":/images/buttonHover.png", ":/images/buttonPress.png", ":/images/buttonChecked.png", this);
    checkableImageButton->move(85, 100);
    connect(checkableImageButton, SIGNAL(clicked()), this, SLOT(buttonClickTest()));
}

void ButtonTab::buttonClickTest()
{
    qDebug() << "clicked";
}
