#ifndef DSEARCHEDIT_H
#define DSEARCHEDIT_H

#include <QFrame>
#include <QSize>
#include <QLineEdit>

#include "libdui_global.h"
#include "dimagebutton.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSearchEdit : public QFrame
{
    Q_OBJECT
public:
    explicit DSearchEdit(QWidget *parent = 0);

    QSize sizeHint() const {return m_size;}
    QSize minimumSizeHint() const {return m_size;}
    void setFixedSize(const QSize & size) {m_size = size;}
    void setMinimumSize(const QSize & size) {m_size = size;}

    void mousePressEvent(QMouseEvent *);
    bool eventFilter(QObject *o, QEvent *e);

signals:
    void textChanged();
    void editingFinished();

public slots:
    void setSearchIcon(const QPixmap & icon) {if (m_btn) m_btn->setNormalPic(icon);}

private:
    QSize m_size;
    QLineEdit *m_edt;
    DImageButton *m_btn;

    const int animationDuration = 400;
};

DUI_END_NAMESPACE

#endif // DSEARCHEDIT_H
