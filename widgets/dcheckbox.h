#ifndef DCHECKBOX_H
#define DCHECKBOX_H

#include <QCheckBox>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit DCheckBox(QWidget *parent = 0);
    explicit DCheckBox(const QString &text, QWidget *parent=0);
};

DUI_END_NAMESPACE

#endif // DCHECKBOX_H
