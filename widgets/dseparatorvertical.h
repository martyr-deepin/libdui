#ifndef DSEPARATORVERTICAL_H
#define DSEPARATORVERTICAL_H

#include <QWidget>
#include <QHBoxLayout>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSeparatorVertical : public QWidget
{
    Q_OBJECT
public:
    explicit DSeparatorVertical(QWidget *parent = 0);

private:
    QWidget *m_leftRec = NULL;
    QWidget *m_rightRec = NULL;
};

DUI_END_NAMESPACE

#endif // DSEPARATORVERTICAL_H
