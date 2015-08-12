#ifndef DCOMBOBOXCOLORDELEGATE_H
#define DCOMBOBOXCOLORDELEGATE_H

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
#include <QDebug>
#include <QPushButton>

#include "libdui_global.h"
#include "dconstants.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT ColorDelegateItem : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor fontColor READ fontColor WRITE setFontColor)
    Q_PROPERTY(int fontPointSize READ fontPointSize WRITE setFontPointSize)
public:
    explicit ColorDelegateItem(QWidget *parent = 0);
    void setData(const QString &color, const QString &title);

    QColor fontColor() const;
    void setFontColor(const QColor &fontColor);

    int fontPointSize() const;
    void setFontPointSize(int fontPointSize);

protected:
    void paintEvent(QPaintEvent *);

private:
    int m_fontPointSize = DUI::FONT_SIZE;
    QColor m_fontColor;
    QColor m_color;
    QString m_title;
    const int COLOR_BLOCK_WIDTH = 25;
    const int COLOR_BLOCK_HEIGHT = 10;
};

class LIBDUISHARED_EXPORT DComboBoxColorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DComboBoxColorDelegate(QObject *parent = 0);
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

DUI_END_NAMESPACE
#endif // DCOMBOBOXCOLORDELEGATE_H
