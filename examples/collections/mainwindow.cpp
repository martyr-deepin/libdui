#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "dslider.h"
#include "dthememanager.h"
#include "libdui_global.h"
#include "dswitchbutton.h"
#include "segmentedcontrol.h"
#include "dcolorpicker.h"

#include "mainwindow.h"
#include "buttonlisttab.h"
#include "buttongridtab.h"
#include "imagebuttongridtab.h"

DUI_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(700, 500);

    DThemeManager * themeManager = DThemeManager::instance();

    initTabWidget();

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_mainTab);

    QHBoxLayout * styleLayout = new QHBoxLayout();
    QPushButton *darkButton = new QPushButton("Dark",this);
    QPushButton *lightBUtton = new QPushButton("Light",this);
    connect(darkButton, &QPushButton::clicked, [=]{
        themeManager->setTheme("dark");
    });
    connect(lightBUtton, &QPushButton::clicked, [=]{
        themeManager->setTheme("light");
    });
    styleLayout->addWidget(darkButton);
    styleLayout->addWidget(lightBUtton);
    styleLayout->addStretch();

    mainLayout->addLayout(styleLayout);

    this->setLayout(mainLayout);
}

void MainWindow::initTabWidget()
{
    m_mainTab = new QTabWidget(this);
    m_mainTab->setFixedSize(this->width(), 450);

    ComboBoxTab * comboBoxTab = new ComboBoxTab(this);
    comboBoxTab->setFixedSize(m_mainTab->size());

    LineTab * lineTab = new LineTab(this);
    lineTab->setFixedSize(m_mainTab->size());

    BarTab * barTab = new BarTab(this);
    barTab->setFixedSize(m_mainTab->size());

    ButtonTab * buttonTab = new ButtonTab(this);
    buttonTab->setFixedSize(m_mainTab->size());

    InputTab * inputTab = new InputTab(this);
    inputTab->setFixedSize(m_mainTab->size());

    SliderTab * sliderTab = new SliderTab(this);
    sliderTab->setFixedSize(m_mainTab->size());

    IndicatorTab * indicatorTab = new IndicatorTab(this);
    indicatorTab->setFixedSize(m_mainTab->size());

    ButtonListTab* buttonListGroupTab = new ButtonListTab(this);
    buttonListGroupTab->setFixedSize(m_mainTab->size());

    ButtonGridTab* buttonGridTab = new ButtonGridTab(this);
    buttonGridTab->setFixedSize(m_mainTab->size());

    ImageButtonGridTab* imageButtonGridTab = new ImageButtonGridTab(this);
    imageButtonGridTab->setFixedSize(m_mainTab->size());
    qDebug() << m_mainTab->size() << "=========";

    Segmentedcontrol *segmentedControl = new Segmentedcontrol(this);

    WidgetsTab *widgetsTab = new WidgetsTab(this);
    widgetsTab->setFixedSize(m_mainTab->size());

    DColorPicker *picker = new DColorPicker(1, this);

    m_mainTab->addTab(comboBoxTab, "ComboBox");
    m_mainTab->addTab(indicatorTab, "Indicator");
    m_mainTab->addTab(lineTab,"Line");
    m_mainTab->addTab(barTab,"Bar");
    m_mainTab->addTab(buttonTab,"Button");
    m_mainTab->addTab(inputTab,"Input");
    m_mainTab->addTab(sliderTab,"Slider");

    m_mainTab->addTab(buttonListGroupTab, "ButtonList");
    m_mainTab->addTab(imageButtonGridTab, "imageButtonGrid");
    m_mainTab->addTab(buttonGridTab, "ButtonGrid");
    m_mainTab->addTab(segmentedControl, "Segmented Control");
    m_mainTab->addTab(widgetsTab, "Widgets");
    m_mainTab->addTab(picker, "Color Picker");

    m_mainTab->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{

}
