#ifndef DCOMBOBOXSIMPLEDELEGATE_H
#define DCOMBOBOXSIMPLEDELEGATE_H

#include <QLabel>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QJsonObject>
#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QColor>
#include <QDebug>
#include <QPushButton>

#include "libdui_global.h"
#include "dconstants.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT FontDelegateItem : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor fontColor READ fontColor WRITE setFontColor)
    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)

public:
    explicit FontDelegateItem(QWidget *parent = 0);
    void setItemFont(const QString &fontName);

    QColor fontColor() const;
    void setFontColor(const QColor &fontColor);

    int fontPixelSize() const;
    void setFontPixelSize(int fontPixelSize);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor m_fontColor;
    int m_fontPixelSize = DUI::FONT_SIZE;
    QString m_fontName;

};

class LIBDUISHARED_EXPORT DComboBoxFontDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DComboBoxFontDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
//    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:

public slots:
};

DUI_END_NAMESPACE

#endif // DCOMBOBOXSIMPLEDELEGATE_H
