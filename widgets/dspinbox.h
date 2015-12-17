#ifndef DSPINBOX_H
#define DSPINBOX_H

#include <QSpinBox>

#include "libdui_global.h"
#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DSpinBoxPrivate;
class DSpinBox : public QSpinBox, public DObject
{
    Q_OBJECT

    Q_PROPERTY(bool alert READ isAlert WRITE setAlert NOTIFY alertChanged)
    Q_PROPERTY(int defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)

public:
    explicit DSpinBox(QWidget *parent = 0);

    QLineEdit *lineEdit() const;

    bool isAlert() const;
    int defaultValue() const;

public slots:
    void setAlert(bool alert);
    void setDefaultValue(int defaultValue);

signals:
    void alertChanged(bool alert);
    void defaultValueChanged(int defaultValue);

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DSpinBox)
};

class DDoubleSpinBoxPrivate;
class DDoubleSpinBox : public QDoubleSpinBox, public DObject
{
    Q_OBJECT

    Q_PROPERTY(bool alert READ isAlert WRITE setAlert NOTIFY alertChanged)
    Q_PROPERTY(double defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)

public:
    explicit DDoubleSpinBox(QWidget *parent = 0);

    bool isAlert() const;
    double defaultValue() const;

public slots:
    void setAlert(bool alert);
    void setDefaultValue(double defaultValue);

signals:
    void alertChanged(bool alert);
    void defaultValueChanged(double defaultValue);

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DDoubleSpinBox)
    double m_defaultValue;
};

DUI_END_NAMESPACE

#endif // DSPINBOX_H
