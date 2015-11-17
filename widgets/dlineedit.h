#ifndef DLINEEDIT_H
#define DLINEEDIT_H

#include <QLineEdit>

#include "libdui_global.h"
#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DLineEditPrivate;
class LIBDUISHARED_EXPORT DLineEdit : public QLineEdit, public DObject
{
    Q_OBJECT
    D_DECLARE_PRIVATE(DLineEdit)
    Q_PROPERTY(bool alert READ isAlert NOTIFY alertChanged)

public:
    DLineEdit(QWidget *parent = 0);

    void setAlert(bool isAlert);
    bool isAlert() const;

signals:
    void alertChanged() const;
    void focusChanged(bool onFocus) const;

protected:
    void focusInEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
};

DUI_END_NAMESPACE

#endif // DLINEEDIT_H
