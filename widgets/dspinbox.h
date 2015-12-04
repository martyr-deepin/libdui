#ifndef DSPINBOX_H
#define DSPINBOX_H

#include <QSpinBox>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DSpinBox : public QSpinBox
{
public:
    explicit DSpinBox(QWidget *parent = 0);

    QLineEdit *lineEdit() const;
};

DUI_END_NAMESPACE

#endif // DSPINBOX_H
