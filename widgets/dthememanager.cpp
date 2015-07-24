#include <QApplication>
#include <QFile>
#include <QDebug>

#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

class DThemeManagerPrivate : public DThemeManager
{

};

Q_GLOBAL_STATIC(DThemeManagerPrivate, DThemeManagerStatic)

DThemeManager * DThemeManager::instance()
{
    return DThemeManagerStatic;
}

void DThemeManager::setTheme(QString) const
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

// private methods
DThemeManager::DThemeManager() :
    QObject()
{
    this->setTheme("");
}

DUI_END_NAMESPACE
