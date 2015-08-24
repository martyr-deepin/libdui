#ifndef DSCROLLAREA_H
#define DSCROLLAREA_H

#include <QScrollArea>
#include <QTimer>
#include <QPropertyAnimation>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DScrollBar;
class LIBDUISHARED_EXPORT DScrollArea : public QScrollArea
{
    Q_OBJECT

    Q_PROPERTY(bool autoHideScrollBar READ autoHideScrollBar WRITE setAutoHideScrollBar NOTIFY autoHideScrollBarChanged)

public:
    explicit DScrollArea(QWidget *parent = 0);
    bool autoHideScrollBar() const;

public slots:
    void setAutoHideScrollBar(bool autoHideScrollBar);

signals:
    void autoHideScrollBarChanged(bool autoHideScrollBar);

private slots:
    void hideScrollBar(QScrollBar *bar);
    void showScrollBar(QScrollBar *bar);

private:
    bool m_autoHideScrollBar;
    DScrollBar *m_vBar, *m_hBar;
    QPropertyAnimation *m_scrollBarAnimation;
    QTimer *m_timer;
};

DUI_END_NAMESPACE

#endif // DSCROLLAREA_H
