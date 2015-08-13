#ifndef COMBOBOXTAB_H
#define COMBOBOXTAB_H

#include <QWidget>
#include <QLabel>
#include <QJsonObject>
#include <QAbstractItemView>
#include "dcombobox.h"
#include "dcomboboxmodel.h"
#include "dfontcombobox.h"
#include "dcolorcombobox.h"
#include "dsimplecombobox.h"

DUI_USE_NAMESPACE

class ComboBoxTab : public QLabel
{
    Q_OBJECT
public:
    explicit ComboBoxTab(QWidget *parent = 0);

signals:

private:
    DComboBox *colorCB;
    DComboBoxModel * colorModel;
    DComboBox *cb;
    DComboBoxModel * model;
    DComboBox *simpleBox;
};

#endif // COMBOBOXTAB_H
