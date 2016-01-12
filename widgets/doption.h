#ifndef DOPTION_H
#define DOPTION_H

#include "libdui_global.h"
#include "dobject.h"

#include <QFrame>
#include <QHBoxLayout>

DUI_BEGIN_NAMESPACE

class DOptionPrivate;
class LIBDUISHARED_EXPORT DOption : public QFrame, public DObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DOption)
    D_DECLARE_PRIVATE(DOption)
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(QString checkedIcon READ checkedIcon WRITE setCheckedIcon NOTIFY checkedIconChanged DESIGNABLE true)

public:
    DOption(QWidget *parent = nullptr);
    void setName(const QString &name);
    void setValue(const QString &value);
    void setIcon(const QString &icon);
    void setIcon(const QPixmap &icon);

    const QString value() const;
    const QString name() const;

    bool checked() const;
    void setChecked(bool checked);
    const QString checkedIcon() const;
    void setCheckedIcon(const QString &icon);

    QHBoxLayout *layout();

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void sizeChanged(const QSize &size) const;
    void checkedChanged(bool checked) const;
    void checkedIconChanged(const QString checkedIcon) const;
};

DUI_END_NAMESPACE

#endif // DOPTION_H
