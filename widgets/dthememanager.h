#ifndef DTHEMEMANAGER_H
#define DTHEMEMANAGER_H

#include <QObject>
#include <QGlobalStatic>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DThemeManager : public QObject
{
    Q_OBJECT

public:
    static DThemeManager * instance();

    void setTheme(QString theme) const;

protected:
    DThemeManager();
};

DUI_END_NAMESPACE

#endif // DTHEMEMANAGER_H
