#ifndef DSEARCHEDIT_H
#define DSEARCHEDIT_H

#include <QWidget>
#include <QSize>

#include "libdui_global.h"
#include "dimagebutton.h"
#include "dlineedit.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSearchEdit : public QWidget
{
    Q_OBJECT
public:
    explicit DSearchEdit(QWidget *parent = 0);

    QSize sizeHint() const {return m_size;}
    QSize minimumSizeHint() const {return m_size;}
    void setFixedSize(const QSize & size) {m_size = size;}
    void setMinimumSize(const QSize & size) {m_size = size;}

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

public slots:
    void setSearchIcon(const QPixmap & icon) {m_btn.setNormalPic(icon);}

private:
    QSize m_size;
    DLineEdit m_edt;
    DImageButton m_btn;

    const int animationDuration = 400;
};

DUI_END_NAMESPACE

#endif // DSEARCHEDIT_H
