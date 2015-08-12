#ifndef DSIMPLECOMBOBOX_H
#define DSIMPLECOMBOBOX_H

#include <QObject>

#include "libdui_global.h"
#include "dcombobox.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSimpleComboBox : public DComboBox
{
    Q_OBJECT
public:
    explicit DSimpleComboBox(QWidget *parent = 0);

signals:

public slots:
};

DUI_END_NAMESPACE

#endif // DSIMPLECOMBOBOX_H
