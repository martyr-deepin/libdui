#ifndef COMBOBOXTAB_H
#define COMBOBOXTAB_H

#include <QWidget>
#include <QLabel>
#include <QJsonObject>
#include <QAbstractItemView>
#include "dcombobox.h"
#include "dcomboboxfontdelegate.h"
#include "dcomboboxmodel.h"

DUI_USE_NAMESPACE

class ComboBoxTab : public QLabel
{
    Q_OBJECT
public:
    explicit ComboBoxTab(QWidget *parent = 0);

signals:

public slots:

private:
    DComboBox *cb;
    DComboBoxModel * model;
};

#endif // COMBOBOXTAB_H
