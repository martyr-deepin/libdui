#include "dthemehelper.h"

DThemeHelper::DThemeHelper(QObject *parent) :
    QObject(parent)
{

}

QString DThemeHelper::themeToQss(QString theme)
{
    return theme;
}

QString DThemeHelper::trimThemeContents(QString qss)
{
    return qss;
}
