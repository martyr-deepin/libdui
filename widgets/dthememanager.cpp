#include <QApplication>
#include <QFile>

#include "dthememanager.h"

DThemeManager::DThemeManager(QObject *parent) :
    QObject(parent)
{
    QApplication * app = qobject_cast<QApplication*>(QApplication::instance());
    if (app != NULL) {
        QFile themeFile(":/dark/theme.qss");

        if (themeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            app->setStyleSheet(themeFile.readAll());
            themeFile.close();
        }
    }
}
