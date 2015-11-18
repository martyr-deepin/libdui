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
    Q_DISABLE_COPY(DLineEdit)
    D_DECLARE_PRIVATE(DLineEdit)
    Q_PROPERTY(bool alert READ isAlert NOTIFY alertChanged)
    Q_PROPERTY(QString normalIcon READ normalIcon WRITE setNormalIcon DESIGNABLE true)
    Q_PROPERTY(QString hoverIcon READ hoverIcon WRITE setHoverIcon DESIGNABLE true)
    Q_PROPERTY(QString pressIcon READ pressIcon WRITE setPressIcon DESIGNABLE true)

public:
    DLineEdit(QWidget *parent = 0);

    void setAlert(bool isAlert);
    bool isAlert() const;

    void setIconVisible(bool visible);
    bool iconVisible() const;

    const QString normalIcon();
    void setNormalIcon(const QString &normalIcon);
    const QString hoverIcon();
    void setHoverIcon(const QString &hoverIcon);
    const QString pressIcon();
    void setPressIcon(const QString &pressIcon);

Q_SIGNALS:
    void iconClicked() const;
    void alertChanged() const;
    void focusChanged(bool onFocus) const;
    void sizeChanged(const QSize &size) const;

protected:
    DLineEdit(DLineEditPrivate &q, QWidget *parent);

    void focusInEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

    Q_PRIVATE_SLOT(d_func(), void _q_resizeInsideFrame(const QSize &))
};

DUI_END_NAMESPACE

#endif // DLINEEDIT_H
