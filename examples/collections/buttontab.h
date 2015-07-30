#ifndef BUTTONTAB_H
#define BUTTONTAB_H

#include <QWidget>
#include <QLabel>

#include "dheaderline.h"
#include "darrowbutton.h"

DUI_USE_NAMESPACE

class ButtonTab : public QLabel
{
    Q_OBJECT
public:
    explicit ButtonTab(QWidget *parent = 0);

signals:

public slots:
};

#endif // BUTTONTAB_H
