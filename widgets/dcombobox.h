#ifndef DCOMBOBOX_H
#define DCOMBOBOX_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QComboBox>
#include <QAbstractItemView>

#include "libdui_global.h"
#include "dconstants.h"
#include "dcomboboxmodel.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit DComboBox(QWidget *parent = 0);

private slots:
    void slotCurrentIndexChange(int index);

private:
    QLabel *m_maskLabel = NULL;    //mask label

    const int MAX_VISIBLE_ITEMS = 16;
};

DUI_END_NAMESPACE

#endif // DCOMBOBOX_H
