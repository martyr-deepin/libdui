#ifndef DTHEMEHELPER_H
#define DTHEMEHELPER_H

#include <QObject>

class DThemeHelper : public QObject
{
    Q_OBJECT
public:
    explicit DThemeHelper(QObject *parent = 0);

    QString themeToQss(QString theme);
    QString trimThemeContents(QString qss);
};

#endif // DTHEMEHELPER_H
