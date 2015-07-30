#ifndef DAPPLICATION_H
#define DAPPLICATION_H

#include <QApplication>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DApplication : public QApplication
{
    Q_OBJECT
public:
    DApplication(int &argc, char **argv);

    QString theme() const;
    void setTheme(const QString & theme);
};

DUI_END_NAMESPACE

#endif // DAPPLICATION_H
