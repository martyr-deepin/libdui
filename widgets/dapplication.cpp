#include <QDebug>

#include "dapplication.h"
#include "dthememanager.h"
#include "private/dthemehelper.h"

DUI_BEGIN_NAMESPACE

DApplication::DApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{

}

QString DApplication::theme() const
{
    return DThemeManager::instance()->theme();
}

void DApplication::setTheme(const QString & theme)
{
    DThemeManager * themeManager = DThemeManager::instance();
    themeManager->setTheme(theme);
}

DUI_END_NAMESPACE
