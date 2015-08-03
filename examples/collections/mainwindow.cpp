#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "dslider.h"
#include "dthememanager.h"
#include "libdui_global.h"
#include "dswitchbutton.h"
#include "segmentedcontrol.h"

#include "mainwindow.h"
#include "buttonlisttab.h"

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

    m_mainTab->addTab(indicatorTab, "Indicator");
    ButtonListTab* buttonListGroupTab = new ButtonListTab(this);
    buttonListGroupTab->setFixedSize(m_mainTab->size());

    DSwitchButton *switchButton = new DSwitchButton(this);

    Segmentedcontrol *segmentedControl = new Segmentedcontrol(this);
    segmentedControl->setFixedSize(m_mainTab->size());

    m_mainTab->addTab(lineTab,"Line");
    m_mainTab->addTab(barTab,"Bar");
    m_mainTab->addTab(buttonTab,"Button");
    m_mainTab->addTab(inputTab,"Input");
    m_mainTab->addTab(sliderTab,"Slider");

    m_mainTab->addTab(buttonListGroupTab, "ButtonListGroup");
    m_mainTab->addTab(switchButton, "Switch Button");
    m_mainTab->addTab(segmentedControl, "Segmented Control");
}

MainWindow::~MainWindow()
{

}
