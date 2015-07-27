#ifndef DHEADERLINE_H
#define DHEADERLINE_H

#include <QWidget>
#include <QLabel>

#include "libdui_global.h"
#include "dbaseline.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DHeaderLine : public DBaseLine
{
    Q_OBJECT
public:
    explicit DHeaderLine(QWidget *parent = 0);
    void setTitle(const QString &title);
    void setContent(QWidget *content);

private:
    void setLeftContent(QWidget *content);
    void setRightContent(QWidget *content);

private:
    QLabel *m_titleLabel = NULL;
};

DUI_END_NAMESPACE

#endif // DHEADERLINE_H
