#ifndef DSPINBOX_H
#define DSPINBOX_H

#include <QSpinBox>

#include "libdui_global.h"
#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DSpinBoxPrivate;
class DSpinBox : public QSpinBox, public DObject
{
public:
    explicit DSpinBox(QWidget *parent = 0);

    QLineEdit *lineEdit() const;

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DSpinBox)
};

class DDoubleSpinBoxPrivate;
class DDoubleSpinBox : public QDoubleSpinBox, public DObject
{
    Q_OBJECT
public:
    explicit DDoubleSpinBox(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DDoubleSpinBox)
};

DUI_END_NAMESPACE

#endif // DSPINBOX_H
