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
    if (m_theme != theme) {
        m_theme = theme;

        emit themeChanged(theme);
    }
}

QString DThemeManager::getQssForWidget(QString className)
{
    QString qss;

    QFile themeFile(QString(":/%1/%2.theme").arg(m_theme).arg(className));

    if (themeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qss = themeFile.readAll();

        themeFile.close();
    }

    return qss;
}

DThemeManager::DThemeManager() :
    QObject()
{
    this->setTheme("dark");
}


DUI_END_NAMESPACE
