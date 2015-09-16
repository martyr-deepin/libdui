#ifndef DBUTTONGRID_H
#define DBUTTONGRID_H

#include <QTableWidget>
#include <QPushButton>

#include "libdui_global.h"
#include "dconstants.h"

class QButtonGroup;
class QLabel;

DUI_BEGIN_NAMESPACE

class ImageButton: public QPushButton
{
    Q_OBJECT
public:
    ImageButton(const QString& icon, const QString text, bool isNameVisible=true, QWidget *parent = 0);
    ~ImageButton();
    void initUI();
    void initConnect();
    void updateChildWidgets();

public slots:
    void handleChecked(bool checked);
    void handleHover(bool hovered);

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void resizeEvent(QResizeEvent* event);

private:
    QString m_icon;
    QString m_text;
    bool m_isNameVisible;
    QLabel* m_iconLabel = NULL;
    QLabel* m_textLabel = NULL;
};

class ItemButton: public QPushButton
{
    Q_OBJECT
public:
    ItemButton(QString text, QWidget *parent=0);
    ~ItemButton();
signals:
    void mouseEntered(QString buttonId);
    void mouseLeaved(QString buttonId);
protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
private:
    QString m_text;
};
class LIBDUISHARED_EXPORT DButtonGrid : public QTableWidget
{
    Q_OBJECT
public:
    explicit DButtonGrid(QWidget *parent = 0);
    explicit DButtonGrid(int rows, int columns, QWidget *parent = 0);
    ~DButtonGrid();

    void init();
    void initConnect();
    void setItemUnChecked();
    void setItemSize(int width, int height);
    int getCurrentCheckedIndex() const;

public slots:
    void addButton(const QString& label, int index);
    void addButtons(const QStringList& listLabels);
    void addImageButton(const QMap<QString, QString>& imageInfo, int index, bool isNameVisible=true);
    void addImageButtons(const QList<QMap<QString, QString>>& imageInfos, bool isNameVisible=true);
    void addButtonWidget(QPushButton* button, int index);
    void checkButtonByIndex(int index);
    void clear();

private slots:
    void setButtonChecked(int id);

signals:
    void buttonChecked(QString label);
    void buttonCheckedIndexChanged(int index);
    void buttonMouseEntered(QString label);
    void buttonMouseLeaved(QString label);
private:
    QButtonGroup* m_buttonGroup = NULL;
    QStringList m_buttonLabels;
    QList<QMap<QString, QString>> m_imageButtonInfos;
    int m_rowHeight = 40;
    int m_columnWidth = 100;
    int m_currentCheckedIndex = -1;

    void clearData();
};

DUI_END_NAMESPACE

#endif // DBUTTONGRID_H