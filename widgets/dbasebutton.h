#ifndef DBASEBUTTON_H
#define DBASEBUTTON_H

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DBaseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit DBaseButton(QWidget * parent = 0);
    explicit DBaseButton(const QString & text, QWidget * parent = 0);
    explicit DBaseButton(const QIcon & icon, const QString & text, QWidget * parent = 0);

private:
    void initInsideFrame();
};

DUI_END_NAMESPACE

#endif // DBASEBUTTON_H
