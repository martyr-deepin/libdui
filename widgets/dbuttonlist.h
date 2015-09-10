#ifndef DBUTTONLIST_H
#define DBUTTONLIST_H

#include <QListWidget>
#include <QPushButton>
#include "libdui_global.h"

class QButtonGroup;
class QLabel;
class QPoint;
class QResizeEvent;
class QEvent;

class IconButton : public QPushButton{
    Q_OBJECT
public:
    IconButton(const QString& Icon, const QString& text, QWidget* parent=0);

    void initIconLabel();
    void initConnect();
    void setIconLeftMargin(int leftMargin);
    void setIconLabel(const QString& icon);
    void hideIconLabel();
    void updateStyle();

signals:
    void mouseEntered(QString label);
    void mouseLeaved(QString label);

protected:
    void resizeEvent(QResizeEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

private:
    QLabel* m_iconLabel;
    QString m_icon;
    QString m_text;
};


DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DButtonList : public QListWidget
{
    Q_OBJECT
public:
    explicit DButtonList(QWidget *parent = 0);
    ~DButtonList();

    void initMargins(int leftMargin, int rightMargin, int imageLeftMargin);

public slots:
    void addButton(const QString &label);
    void addButton(const QString& label, int index);
    void addButtons(const QStringList& listLabels);
    void setItemHeight(int height);
    void setItemWidth(int width);
    void setItemSize(int width, int height);
    void setItemSize(QSize size);
    void checkButtonByIndex(int index);
    void clear();

private slots:
    void setButtonChecked(int id);
    IconButton* getButtonByIndex(int index);

signals:
    void buttonChecked(QString label);
    void buttonCheckedIndexChanged(int index);
    void buttonMouseEntered(QString label);
    void buttonMouseLeaved(QString label);

private:
    QButtonGroup* m_buttonGroup = NULL;

    void initConnect();

    int m_leftMargin = 10;
    int m_rightMargin = 10;
    int m_imageLeftMargin = 10;
};


DUI_END_NAMESPACE

#endif // DBUTTONLIST_H
