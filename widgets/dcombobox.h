#ifndef DCOMBOBOX_H
#define DCOMBOBOX_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QComboBox>
#include <QListView>
#include <QAbstractItemView>

#include "libdui_global.h"
#include "dconstants.h"
#include "dcomboboxmodel.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DComboBox : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QString normalTickImg READ normalTickImg WRITE setNormalTickImg)
    Q_PROPERTY(QString hoverTickImg READ hoverTickImg WRITE setHoverTickImg)
    Q_PROPERTY(QString insensitiveTickImg READ insensitiveTickImg WRITE setInsensitiveTickImg)
public:
    explicit DComboBox(QWidget *parent = 0);
    void setFixedSize(int w, int h);
    void setFixedSize(QSize size);

    QString normalTickImg() const;
    void setNormalTickImg(const QString &normalTickImg);
    QString hoverTickImg() const;
    void setHoverTickImg(const QString &hoverTickImg);
    QString insensitiveTickImg() const;
    void setInsensitiveTickImg(const QString &insensitiveTickImg);

private slots:
    void slotCurrentIndexChange(int index);

private:
    QLabel *m_maskLabel = NULL;    //mask label

    QString m_normalTickImg = "";
    QString m_hoverTickImg = "";
    QString m_insensitiveTickImg = "";

    const int MAX_VISIBLE_ITEMS = 16;
};

DUI_END_NAMESPACE

#endif // DCOMBOBOX_H
