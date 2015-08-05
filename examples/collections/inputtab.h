#ifndef INPUTTAB_H
#define INPUTTAB_H

#include <QWidget>

#include "dpasswordedit.h"
#include "dsearchedit.h"
#include "dlineedit.h"

class InputTab : public QWidget
{
    Q_OBJECT
public:
    explicit InputTab(QWidget *parent = 0);
};

#endif // INPUTTAB_H
