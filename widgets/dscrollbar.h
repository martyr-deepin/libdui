#ifndef DSCROLLBAR_H
#define DSCROLLBAR_H

#include <QScrollBar>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit DScrollBar(QWidget *parent = 0);

signals:

public slots:
};

DUI_END_NAMESPACE

#endif // DSCROLLBAR_H
