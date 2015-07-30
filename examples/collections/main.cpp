#include "mainwindow.h"

#include <dapplication.h>

DUI_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    a.setTheme("dark");

    MainWindow w;
    w.show();

    return a.exec();
}
