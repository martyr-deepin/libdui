#ifndef LINETAB_H
#define LINETAB_H

#include <QWidget>
#include <QPushButton>
#include <libdui/dheaderline.h>
#include <libdui/dbaseline.h>
#include <libdui/dseparatorhorizontal.h>
#include <libdui/dseparatorvertical.h>
#include <libdui/dbaseexpand.h>
#include <libdui/darrowlineexpand.h>

DUI_USE_NAMESPACE

class LineTab : public QLabel
{
    Q_OBJECT
public:
    explicit LineTab(QWidget *parent = 0);

signals:

public slots:
};

#endif // LINETAB_H
