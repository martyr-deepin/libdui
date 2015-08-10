#ifndef DCOMBOBOX_H
#define DCOMBOBOX_H

#include <QWidget>
#include <QComboBox>

#include "libdui_global.h"
#include "dconstants.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit DComboBox(QWidget *parent = 0);

signals:

public slots:
};

DUI_END_NAMESPACE

#endif // DCOMBOBOX_H
