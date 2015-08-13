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

class FontDelegateItem : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor fontNormalColor READ fontNormalColor WRITE setFontNormalColor)
    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)

public:
    explicit FontDelegateItem(QWidget *parent = 0);
    void setItemFont(const QString &family, const QString &title);

    QColor fontNormalColor() const;
    void setFontNormalColor(const QColor &fontNormalColor);

    int fontPixelSize() const;
    void setFontPixelSize(int fontPixelSize);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_fontTitle = "";
    QString m_fontFamily = "";
    QColor m_fontNormalColor;
    int m_fontPixelSize = DUI::FONT_SIZE;

};

class DComboBoxFontDelegate : public DAbstractComboBoxDelegate
{
    Q_OBJECT
public:
    explicit DComboBoxFontDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};

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

private:
    DComboBoxModel *m_fontModel = NULL;
};

DUI_END_NAMESPACE

#endif // DFONTCOMBOBOX_H
