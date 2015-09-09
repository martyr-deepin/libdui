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
    Q_PROPERTY(bool isEchoMode READ isEchoMode NOTIFY echoModeChanged)
    Q_PROPERTY(bool isAlertMode READ isAlertMode NOTIFY alertModeChanged)

public:
    explicit DPasswordEdit(QWidget *parent = 0);

    inline QString text() const {return m_edit.text();}
    inline bool isEchoMode() const {return m_echo;}
    inline bool isAlertMode() const {return m_alert;}

signals:
    void echoModeChanged();
    void alertModeChanged();
    void focusChanged(bool onFocus);
    void textChanged(const QString text);

public slots:
    inline void setPassword(const QString & password) {m_edit.setText(password);}
    void setEchoMode(const bool isEcho);
    void setAlertMode(const bool isAlert);

private slots:
    bool eventFilter(QObject *o, QEvent *e);

private:
    QLineEdit m_edit;
    DImageButton m_btn;

    bool m_alert = false;
    bool m_echo = false;
};

DUI_END_NAMESPACE

#endif // DPASSWORDEDIT_H
