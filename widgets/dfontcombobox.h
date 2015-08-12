#ifndef DFONTCOMBOBOX_H
#define DFONTCOMBOBOX_H

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

#include "libdui_global.h"
#include "dcombobox.h"

DUI_BEGIN_NAMESPACE

class FontDelegateItem : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor fontColor READ fontColor WRITE setFontColor)
    Q_PROPERTY(int fontPointSize READ fontPointSize WRITE setFontPointSize)

public:
    explicit FontDelegateItem(QWidget *parent = 0);
    void setItemFont(const QString &fontName);

    QColor fontColor() const;
    void setFontColor(const QColor &fontColor);

    int fontPointSize() const;
    void setFontPointSize(int fontPointSize);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor m_fontColor;
    int m_fontPointSize = DUI::FONT_SIZE;
    QString m_fontName;

};

class DComboBoxFontDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DComboBoxFontDelegate(QObject *parent = 0);
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
//    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

};

class LIBDUISHARED_EXPORT DFontComboBox : public DComboBox
{
    Q_OBJECT
public:
    explicit DFontComboBox(QWidget *parent = 0);
    void addFontName(const QString &name);

signals:
    void currentFontNameChange(QString name);

private slots:
    void onCurrentIndexChange(int index);

private:
    DComboBoxModel *m_fontModel = NULL;
};

DUI_END_NAMESPACE

#endif // DFONTCOMBOBOX_H
