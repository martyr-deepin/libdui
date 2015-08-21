#ifndef DSEARCHEDIT_H
#define DSEARCHEDIT_H

#include <QFrame>
#include <QSize>
#include <QLineEdit>
#include <QPropertyAnimation>

#include "libdui_global.h"
#include "dimagebutton.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DSearchEdit : public QFrame
{
    Q_OBJECT
public:
    explicit DSearchEdit(QWidget *parent = 0);
    ~DSearchEdit();

    QSize sizeHint() const {return m_size;}
    QSize minimumSizeHint() const {return m_size;}
    void setFixedSize(const QSize & size) {m_size = size;}
    void setMinimumSize(const QSize & size) {m_size = size;}
    const QString text() const;

    void mousePressEvent(QMouseEvent *);
    bool eventFilter(QObject *o, QEvent *e);

    inline void setAniDuration(const int duration) {m_animation->setDuration(duration);}
    inline void setAniShowCurve(const QEasingCurve curve) {m_showCurve = curve;}
    inline void setAniHideCurve(const QEasingCurve curve) {m_hideCurve = curve;}

public slots:
    void setText(const QString & text) {if (m_edt) m_edt->setText(text);}
    void setSearchIcon(const QString & icon) {if (m_btn) m_btn->setNormalPic(icon);}

signals:
    void textChanged();
    void editingFinished();

private slots:
    void toEditMode();

private:
    QSize m_size;
    QLineEdit *m_edt;
    DImageButton *m_btn;

    QPropertyAnimation *m_animation;
    QEasingCurve m_showCurve = QEasingCurve::OutCubic;
    QEasingCurve m_hideCurve = QEasingCurve::InCubic;
};

DUI_END_NAMESPACE

#endif // DSEARCHEDIT_H
