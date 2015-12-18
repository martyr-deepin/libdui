#ifndef DSIMPLECOMBOBOX_H
#define DSIMPLECOMBOBOX_H

#include <QWidget>

#include "libdui_global.h"
#include "dcomboboxmodel.h"
#include "dabstractcomboboxdelegate.h"
#include "dcombobox.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSimpleComboBox : public DComboBox
{
    Q_OBJECT
public:
    explicit DSimpleComboBox(QWidget *parent = 0);

    void addItem(const QString &text);
    void addItems(const QStringList &texts);

signals:
    void currentTextChanged(const QString &);

private:
    Q_SLOT void onCurrentIndexChange(int index);
};

DUI_END_NAMESPACE

#endif // DSIMPLECOMBOBOX_H
