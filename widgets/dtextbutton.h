#ifndef DTEXTBUTTON_H
#define DTEXTBUTTON_H

#include <QPushButton>
#include <QPainter>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DTextButton : public QPushButton
{
    Q_OBJECT
public:
    DTextButton(const QString & text, QWidget * parent = 0);
    ~DTextButton();
};

DUI_END_NAMESPACE

#endif // DTEXTBUTTON_H
