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

class ColorDelegateItem : public QLabel
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
    QColor m_fontColor;
    QColor m_color;
    QString m_title;
    int m_fontPointSize = DUI::FONT_SIZE;
    const int COLOR_BLOCK_WIDTH = 25;
    const int COLOR_BLOCK_HEIGHT = 10;
};

class DComboBoxColorDelegate : public DAbstractComboBoxDelegate
{
    Q_OBJECT
public:
    explicit DComboBoxColorDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

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
    DComboBoxModel *m_colorModel = NULL;
};

DUI_END_NAMESPACE

#endif // DCOLORCOMBOBOX_H
