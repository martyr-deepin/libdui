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
    const QString text() const;

    void mousePressEvent(QMouseEvent *);
    bool eventFilter(QObject *o, QEvent *e);

    inline void setAniDuration(const int duration) {m_animation->setDuration(duration);}
    inline void setAniShowCurve(const QEasingCurve curve) {m_showCurve = curve;}
    inline void setAniHideCurve(const QEasingCurve curve) {m_hideCurve = curve;}

public slots:
    void setText(const QString & text) {if (m_edt) m_edt->setText(text);}
    inline void clear() {m_edt->clear();}

signals:
    void textChanged();
    void editingFinished();

private slots:
    void toEditMode();

private:
    void initInsideFrame();
    void resizeEvent(QResizeEvent *e);

private:
    QSize m_size;
    QLineEdit *m_edt;
    DImageButton *m_searchBtn;
    DImageButton *m_clearBtn;
    QFrame *m_insideFrame = NULL;

    QPropertyAnimation *m_animation;
    QEasingCurve m_showCurve = QEasingCurve::OutCubic;
    QEasingCurve m_hideCurve = QEasingCurve::InCubic;
};

DUI_END_NAMESPACE

#endif // DSEARCHEDIT_H
