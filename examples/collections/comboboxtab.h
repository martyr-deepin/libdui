#ifndef COMBOBOXTAB_H
#define COMBOBOXTAB_H

#include <QWidget>
#include <QLabel>
#include "dcombobox.h"

DUI_USE_NAMESPACE

class ComboBoxTab : public QLabel
{
    Q_OBJECT
public:
    explicit ComboBoxTab(QWidget *parent = 0);

signals:

public slots:
};

#endif // COMBOBOXTAB_H
