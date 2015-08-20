#ifndef DLABEL_H
#define DLABEL_H


#include <QLabel>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DLabel : public QLabel
{
    Q_OBJECT

public:
    DLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    DLabel(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0);
};

DUI_END_NAMESPACE

#endif // DLABEL_H
