#include <QApplication>
#include <QFile>

#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DThemeManager::DThemeManager(QObject *parent) :
    QObject(parent)
{
    QApplication * app = qobject_cast<QApplication*>(QApplication::instance());
    if (app != NULL) {
        QFile themeFile(":/dark/theme.qss");

        if (themeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString theme = themeFile.readAll();
            app->setStyleSheet(theme);

            themeFile.close();
        }
    }
}

DUI_END_NAMESPACE
