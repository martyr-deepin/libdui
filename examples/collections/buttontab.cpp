#include "buttontab.h"

#include <QDebug>

DUI_USE_NAMESPACE

ButtonTab::ButtonTab(QWidget *parent) : QLabel(parent)
{
    setStyleSheet("ButtonTab{background-color: #252627;}");

    DArrowButton * arrowButton = new DArrowButton(this);
    arrowButton->setArrowDirection(DArrowButton::ArrowDown);
    arrowButton->move(5, 5);

    DWindowMinButton * minButton = new DWindowMinButton(this);
    minButton->move(30, 5);

    DWindowMaxButton * maxButton = new DWindowMaxButton(this);
    maxButton->move(50, 5);

    DWindowRestoreButton * restoreButton = new DWindowRestoreButton(this);
    restoreButton->move(70, 5);

    DWindowCloseButton * closeButton = new DWindowCloseButton(this);
    closeButton->move(90, 5);

    DWindowOptionButton * optionButton = new DWindowOptionButton(this);
    optionButton->move(110, 5);

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
    imageButton2->setNormalPic(":/images/buttonHover.png");
    imageButton2->move(35, 100);

    DImageButton *checkableImageButton = new DImageButton(":/images/button.png", ":/images/buttonHover.png", ":/images/buttonPress.png", ":/images/buttonChecked.png", this);
    checkableImageButton->move(85, 100);
    connect(checkableImageButton, SIGNAL(clicked()), this, SLOT(buttonClickTest()));

    DSwitchButton *switchButton = new DSwitchButton(this);
    switchButton->move(85, 200);

    DUI::DLinkButton *linkBtn = new DUI::DLinkButton("Link Button", this);
    linkBtn->move(10, 125);

    DUI::DLinkButton *showCalendarBtn = new DUI::DLinkButton("Show Calendar", this);
    showCalendarBtn->move(10, 155);
    connect(showCalendarBtn, &DLinkButton::clicked, [] {
//        (new DUI::DCalendar())->show();
        DUI::DCalendar *calendar = new DUI::DCalendar;
        calendar->setFixedSize(300, 300);

        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(calendar);
        widget->setLayout(layout);
        widget->show();
        widget->setStyleSheet("background-color:black;");
    });
}

void ButtonTab::buttonClickTest()
{
    qDebug() << "clicked";
}
