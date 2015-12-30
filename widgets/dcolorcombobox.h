#ifndef DCOLORCOMBOBOX_H
#define DCOLORCOMBOBOX_H

#include <QLabel>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QJsonObject>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QColor>

#include "libdui_global.h"
#include "dcomboboxmodel.h"
#include "dcombobox.h"
#include "dabstractcomboboxdelegate.h"

DUI_BEGIN_NAMESPACE

class DColorComboBoxPrivate;
class LIBDUISHARED_EXPORT DColorComboBox : public DComboBox
{
    Q_OBJECT
public:
    explicit DColorComboBox(QWidget *parent = 0);
    void addData(const QColor &color, const QString &title);
    void addData(const QString &color, const QString &title);

signals:
    void currentColorChange(QColor color);

public slots:
    void onCurrentIndexChange(int index);

private:
    D_DECLARE_PRIVATE(DColorComboBox)
};

DUI_END_NAMESPACE

#endif // DCOLORCOMBOBOX_H
