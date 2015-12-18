#ifndef DCOMBOBOX_H
#define DCOMBOBOX_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QComboBox>
#include <QListView>
#include <QAbstractItemView>

#include "libdui_global.h"
#include "dobject.h"
#include "dconstants.h"
#include "dcomboboxmodel.h"

DUI_BEGIN_NAMESPACE

class DComboBoxPrivate;

class LIBDUISHARED_EXPORT DComboBox : public QComboBox, public DObject
{
    Q_OBJECT

    Q_PROPERTY(QString normalTickImg READ normalTickImg WRITE setNormalTickImg)
    Q_PROPERTY(QString hoverTickImg READ hoverTickImg WRITE setHoverTickImg)
    Q_PROPERTY(QString insensitiveTickImg READ insensitiveTickImg WRITE setInsensitiveTickImg)
    Q_PROPERTY(bool alert READ isAlert WRITE setAlert NOTIFY alertChanged)

public:
    explicit DComboBox(QWidget *parent = 0);

    void setFixedSize(int w, int h);
    void setFixedSize(QSize size);

    QString normalTickImg() const;
    QString hoverTickImg() const;
    QString insensitiveTickImg() const;
    bool isAlert() const;

    DComboBoxModel *dcomboBoxModel() const;

public Q_SLOTS:
    void setEditable(bool editable);
    void setNormalTickImg(const QString &normalTickImg);
    void setHoverTickImg(const QString &hoverTickImg);
    void setInsensitiveTickImg(const QString &insensitiveTickImg);
    void setAlert(bool alert);

Q_SIGNALS:
    void alertChanged(bool alert);

protected:
    explicit DComboBox(DComboBoxPrivate &dd, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DComboBox)
    Q_PRIVATE_SLOT(d_func(), void _q_slotCurrentIndexChange(int index))
};

DUI_END_NAMESPACE

#endif // DCOMBOBOX_H
