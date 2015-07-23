#include <QHBoxLayout>

#include <libdui/dslider.h>
#include <libdui/dthememanager.h>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    DThemeManager themeManager;

    QHBoxLayout * layout = new QHBoxLayout(this);

    DSlider * slider = new DSlider(Qt::Horizontal);

    layout->addStretch();
    layout->addWidget(slider);
    layout->addStretch();
}

MainWindow::~MainWindow()
{

}
