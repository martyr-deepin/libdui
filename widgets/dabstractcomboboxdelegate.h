#ifndef DABSTRACTCOMBOBOXDELEGATE_H
#define DABSTRACTCOMBOBOXDELEGATE_H

#include <QObject>
#include <QPainter>
#include <QStyledItemDelegate>

#include "dcombobox.h"

class DAbstractComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DAbstractComboBoxDelegate(QObject *parent = 0);
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
//    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

};

#endif // DABSTRACTCOMBOBOXDELEGATE_H
