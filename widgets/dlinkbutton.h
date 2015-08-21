#ifndef DLINKBUTTON_H
#define DLINKBUTTON_H

#include <QPushButton>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DLinkButton : public QPushButton
{
    Q_OBJECT

public:
    DLinkButton(const QString & text = QString(), QWidget * parent = 0);
};

DUI_END_NAMESPACE

#endif // DLINKBUTTON_H
