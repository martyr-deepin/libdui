#ifndef DPASSWORDEDIT_H
#define DPASSWORDEDIT_H

#include <QWidget>
#include <QSize>
#include <QPixmap>
#include <QLineEdit>

#include "dimagebutton.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DPasswordEdit : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(bool isEchoMode READ isEchoMode)
    Q_PROPERTY(bool isAlertMode READ isAlertMode)

public:
    explicit DPasswordEdit(QWidget *parent = 0);

    inline QString text() const {return m_edit.text();}
    inline bool isEchoMode() const {return m_echo;}
    inline bool isAlertMode() const {return m_alert;}

public slots:
    /*inline void setNormalIcon(const QPixmap & icon) {m_btn.setNormalPic(icon);}
    inline void setHoverIcon(const QPixmap & icon) {m_btn.setHoverPic(icon);}
    inline void setShowPasswordIcon(const QPixmap &icon) {m_btn.setCheckedPic(icon);}*/
    inline void setPassword(const QString & password) {m_edit.setText(password);}
    void setEchoMode(const bool isEcho);
    void setAlertMode(const bool isAlert);

signals:
    void textChanged(const QString text);

private:
    QLineEdit m_edit;
    DUI::DImageButton m_btn;

    bool m_alert = false;
    bool m_echo = false;
};

DUI_END_NAMESPACE

#endif // DPASSWORDEDIT_H
