#ifndef DTHEMEMANAGER_H
#define DTHEMEMANAGER_H

#include <QObject>
#include <QString>
#include <QGlobalStatic>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DThemeManager : public QObject
{
    Q_OBJECT

public:
    static DThemeManager * instance();

    QString theme() const;
    void setTheme(const QString theme);

    QString getQssForWidget(QString className);

signals:
    void themeChanged(QString theme);

protected:
    DThemeManager();

    QString m_theme;
};

DUI_END_NAMESPACE

#endif // DTHEMEMANAGER_H
