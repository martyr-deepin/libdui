#ifndef DSWITCHLINEEXPAND_H
#define DSWITCHLINEEXPAND_H

#include <QWidget>

#include "libdui_global.h"
#include "dbaseexpand.h"
#include "dswitchbutton.h"
#include "dheaderline.h"

DUI_BEGIN_NAMESPACE

class SwitchHeaderLine : public DHeaderLine
{
    Q_OBJECT
public:
    SwitchHeaderLine(QWidget *parent = 0);
    void setExpand(bool value);

signals:
    void mousePress();

protected:
    void mousePressEvent(QMouseEvent *);

private:
    void reverseArrowDirection();
    DSwitchButton *m_switchButton = NULL;

};

class LIBDUISHARED_EXPORT DSwitchLineExpand : public DBaseExpand
{
    Q_OBJECT
public:
    explicit DSwitchLineExpand(QWidget *parent = 0);
    void setTitle(const QString &title);
    void setExpand(bool value);

private:
    void setHeader(QWidget *header);
    void resizeEvent(QResizeEvent *e);

private:
    SwitchHeaderLine *m_headerLine = NULL;
};

DUI_END_NAMESPACE

#endif // DSWITCHLINEEXPAND_H
