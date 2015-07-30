#ifndef DBUTTONLIST_H
#define DBUTTONLIST_H

#include <QListWidget>
#include "libdui_global.h"

class QButtonGroup;

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DButtonList : public QListWidget
{
    Q_OBJECT
public:
    explicit DButtonList(QWidget *parent = 0);
    ~DButtonList();

public slots:
    void addButton(const QString& label);
    void addButtons(const QStringList& listLabels);
    void setItemHeight(int height);
    void setItemWidth(int width);
    void setItemSize(int width, int height);
    void setItemSize(QSize size);

    void setButtonChecked(int id);

signals:
    void buttonChecked(QString label);

private:
    QButtonGroup* m_buttonGroup = NULL;

    void initConnect();
};


DUI_END_NAMESPACE

#endif // DBUTTONLIST_H
