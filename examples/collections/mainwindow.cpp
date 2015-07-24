#include <QHBoxLayout>
#include <QPushButton>u

#include <libdui/dslider.h>
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
        themeManager->setTheme("light");
    });
}

MainWindow::~MainWindow()
{

}
