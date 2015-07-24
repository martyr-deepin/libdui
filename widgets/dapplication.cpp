#include <QDebug>

#include "dapplication.h"
#include "dthememanager.h"

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

QString DApplication::styleSheet() const
{
    return QApplication::styleSheet();
}

void DApplication::setStyleSheet(const QString &sheet)
{
    QString old = styleSheet();

    qDebug() << sheet;

    QApplication::setStyleSheet(old + sheet);
}

DUI_END_NAMESPACE
