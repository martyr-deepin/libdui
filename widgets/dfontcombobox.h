#ifndef DFONTCOMBOBOX_H
#define DFONTCOMBOBOX_H

#include <QLabel>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QJsonObject>
#include <QItemDelegate>
#include <QModelIndex>
#include <QCursor>
#include <QColor>

#include "libdui_global.h"
#include "dcombobox.h"
#include "dcomboboxmodel.h"
#include "dabstractcomboboxdelegate.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DFontComboBox : public DComboBox
{
    Q_OBJECT
public:
    explicit DFontComboBox(QWidget *parent = 0);
    void addFontItem(const QString &family, const QString &title = "");

signals:
    void currentFontNameChange(QString name);

private slots:
    void onCurrentIndexChange(int index);
};

DUI_END_NAMESPACE

#endif // DFONTCOMBOBOX_H
