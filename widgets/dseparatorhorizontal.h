#ifndef DSEPARATORHORIZONTAL_H
#define DSEPARATORHORIZONTAL_H

#include <QWidget>
#include <QVBoxLayout>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSeparatorHorizontal : public QWidget
{
    Q_OBJECT
public:
    explicit DSeparatorHorizontal(QWidget *parent = 0);

private:
    QWidget *m_topRec = NULL;
    QWidget *m_bottomRec = NULL;
};

DUI_END_NAMESPACE

#endif // DSEPARATORHORIZONTAL_H
