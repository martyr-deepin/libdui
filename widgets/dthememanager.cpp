#include <QFile>
#include <QDebug>

#include "dthememanager.h"
#include "dapplication.h"
#include "private/dthemehelper.h"

DUI_BEGIN_NAMESPACE

class DThemeManagerPrivate : public DThemeManager
{

};

Q_GLOBAL_STATIC(DThemeManagerPrivate, DThemeManagerStatic)

DThemeManager * DThemeManager::instance()
{
    return DThemeManagerStatic;
}

QString DThemeManager::theme() const
{
    return m_theme;
}

void DThemeManager::setTheme(const QString theme)
{


    DApplication * app = qobject_cast<DApplication*>(DApplication::instance());
    if (app != NULL) {
        QFile themeFile(QString(":/%1/%1.theme").arg(theme));

        if (themeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            m_theme = theme;

            QString style = themeFile.readAll();

            DThemeHelper helper;
            app->setStyleSheet(helper.themeToQss(style));

            themeFile.close();
        }
    }
}

// private methods
DThemeManager::DThemeManager() :
    QObject()
{
    this->setTheme("dark");
}


DUI_END_NAMESPACE
