#ifndef DLINEEDIT_H
#define DLINEEDIT_H

#include <QLineEdit>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    DLineEdit(QWidget *parent = 0);
};

DUI_END_NAMESPACE

#endif // DLINEEDIT_H
