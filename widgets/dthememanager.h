#ifndef DTHEMEMANAGER_H
#define DTHEMEMANAGER_H

#include <QObject>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DThemeManager : public QObject
{
    Q_OBJECT
public:
    DThemeManager(QObject *parent = 0);
};

DUI_END_NAMESPACE

#endif // DTHEMEMANAGER_H
