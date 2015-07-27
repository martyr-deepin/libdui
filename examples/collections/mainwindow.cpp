#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

#include <libdui/dslider.h>
#include <libdui/dbaseline.h>
#include <libdui/dseparatorhorizontal.h>
#include <libdui/dseparatorvertical.h>
#include <libdui/dthememanager.h>
#include <libdui/libdui_global.h>

#include "mainwindow.h"

DUI_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    DThemeManager * themeManager = DThemeManager::instance();

    QHBoxLayout * layout = new QHBoxLayout(this);

    DSlider * slider = new DSlider(Qt::Horizontal);

    layout->addStretch();
    layout->addWidget(slider);
    layout->addStretch();

    QPushButton * button = new QPushButton("theme");

    layout->addWidget(button);

    connect(button, &QPushButton::clicked, [=] {

        if (themeManager->theme() == "light") {
            themeManager->setTheme("dark");
        } else {
            themeManager->setTheme("light");
        }
    });


    DSeparatorHorizontal *dsHorizontal = new DSeparatorHorizontal(this);
    dsHorizontal->setFixedSize(200,2);
    dsHorizontal->move(1,5);
    DSeparatorVertical *dsVertical = new DSeparatorVertical(this);
    dsVertical->setFixedSize(2,200);
    dsVertical->move(10,5);

    DBaseLine * baseLine = new DBaseLine(this);
    baseLine->setFixedSize(400,30);
    baseLine->move(20,30);
    baseLine->setLeftContent(new QLabel("DBaseLine"));
    QPushButton *bbb = new QPushButton("Test button",this);
    bbb->setStyleSheet("background-color: red");
    baseLine->setRightContent(bbb);

    this->setFixedSize(500,500);
}

MainWindow::~MainWindow()
{

}
