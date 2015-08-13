#ifndef DSIMPLECOMBOBOX_H
#define DSIMPLECOMBOBOX_H

#include <QWidget>

#include "libdui_global.h"
#include "dcomboboxmodel.h"
#include "dabstractcomboboxdelegate.h"
#include "dcombobox.h"

DUI_BEGIN_NAMESPACE

class SimpleDelegateItem : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor fontNormalColor READ fontNormalColor WRITE setFontNormalColor)
    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)
public:
    explicit SimpleDelegateItem(QWidget *parent = 0);
    void setText(const QString &text);

    QColor fontNormalColor() const;
    void setFontNormalColor(const QColor &fontNormalColor);

    int fontPixelSize() const;
    void setFontPixelSize(int fontPixelSize);

protected:
    void paintEvent(QPaintEvent *);

private:
    QString m_text = "";
    QColor m_fontNormalColor;
    int m_fontPixelSize = DUI::FONT_SIZE;
};

class DComboBoxSimpleDelegate : public DAbstractComboBoxDelegate
{
    Q_OBJECT
public:
    explicit DComboBoxSimpleDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
};


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
    void onCurrentIndexChange(int index);

private:
    DComboBoxModel *m_simpleModel = NULL;

};

DUI_END_NAMESPACE

#endif // DSIMPLECOMBOBOX_H
