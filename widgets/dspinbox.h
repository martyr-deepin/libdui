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

class DDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit DDoubleSpinBox(QWidget *parent = 0);
};

DUI_END_NAMESPACE

#endif // DSPINBOX_H
