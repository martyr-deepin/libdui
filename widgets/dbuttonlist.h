#ifndef DBUTTONLIST_H
#define DBUTTONLIST_H

#include <QListWidget>
#include <QPushButton>
#include "libdui_global.h"

class QButtonGroup;
class QLabel;
class QPoint;
class QResizeEvent;

class IconButton : public QPushButton{
    Q_OBJECT
public:
    IconButton(const QString& Icon, const QString& text, QWidget* parent=0);

    void initIconLabel();
    void initConnect();
    void setIconLeftMargin(int leftMargin);
    void setIconLabel(const QString& Icon);
    void hideIconLabel();
    void updateStyle();

protected:
    void resizeEvent(QResizeEvent* event);

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

    IconButton* getButtonByIndex(int index);

private slots:
    void setButtonChecked(int id);

signals:
    void buttonChecked(QString label);
    void buttonCheckedIndexChanged(int index);

private:
    QButtonGroup* m_buttonGroup = NULL;

    void initConnect();

    int m_leftMargin = 10;
    int m_rightMargin = 10;
    int m_imageLeftMargin = 10;
};


DUI_END_NAMESPACE

#endif // DBUTTONLIST_H
