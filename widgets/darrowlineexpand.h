#ifndef DARROWLINEEXPAND_H
#define DARROWLINEEXPAND_H

#include <QWidget>

#include "libdui_global.h"
#include "dbaseexpand.h"
#include "darrowbutton.h"
#include "dheaderline.h"

DUI_BEGIN_NAMESPACE

class ArrowHeaderLine : public DHeaderLine
{
    Q_OBJECT
public:
    ArrowHeaderLine(QWidget *parent = 0);
    void setExpand(bool value);

signals:
    void mousePress();

protected:
    void mousePressEvent(QMouseEvent *);

private:
    void reverseArrowDirection();
    DArrowButton *m_arrowButton = NULL;

};

class LIBDUISHARED_EXPORT DArrowLineExpand : public DBaseExpand
{
    Q_OBJECT
public:
    explicit DArrowLineExpand(QWidget *parent = 0);
    void setTitle(const QString &title);
    void setExpand(bool value);

private:
    void setHeader(QWidget *header);
    void resizeEvent(QResizeEvent *e);

private:
    ArrowHeaderLine *m_headerLine = NULL;
};

DUI_END_NAMESPACE

#endif // DARROWLINEEXPAND_H
