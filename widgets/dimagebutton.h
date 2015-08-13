#ifndef DIMAGEBUTTON_H
#define DIMAGEBUTTON_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DImageButton : public QLabel
{
    Q_OBJECT

public:
    DImageButton(QWidget * parent=0);

    DImageButton(const QString & normalPic, const QString & hoverPic,
                 const QString & pressPic, QWidget *parent = 0);

    DImageButton(const QString & normalPic, const QString & hoverPic,
                 const QString & pressPic, const QString & checkedPic, QWidget * parent = 0);

    ~DImageButton();

    void enterEvent(QEvent * event) ;
    void leaveEvent(QEvent * event) ;
    void mousePressEvent(QMouseEvent * event) ;
    void mouseReleaseEvent(QMouseEvent * event) ;

    void setChecked(bool flag);
    void setCheckable(bool flag);
    bool isChecked();
    bool isCheckable();

    void setNormalPic(const QPixmap & normalPicPixmap);
    void setHoverPic(const QPixmap & hoverPicPixmap);
    void setPressPic(const QPixmap & pressPicPixmap);
    void setCheckedPic(const QPixmap & checkedPicPixmap);

    enum State {Normal, Hover, Press, Checked};

    State getState() const;

signals:
    void clicked();
    void stateChanged();

private:
    void changeState();

private:

    State m_state = Normal;

    bool m_isChecked = false;
    bool m_isCheckable = false;
    QPixmap m_normalPic;
    QPixmap m_hoverPic;
    QPixmap m_pressPic;
    QPixmap m_checkedPic;
};

DUI_END_NAMESPACE

#endif // DIMAGEBUTTON_H
