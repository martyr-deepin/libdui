#ifndef DSHORTCUTEDIT_H
#define DSHORTCUTEDIT_H

#include <QFrame>
#include <QLabel>
#include <QString>
#include <QRegExp>
#include <QColor>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class DShortcutEditLabel;
class LIBDUISHARED_EXPORT DShortcutEdit : public QFrame
{
    Q_OBJECT

public:
    DShortcutEdit(QWidget *parent = 0);

    QSize sizeHint() const;
    bool eventFilter(QObject *o, QEvent *e);
    static bool isValidShortcutKey(const QString & key);

signals:
    void shortcutKeysChanged(const QString & shortcutKeys);
    void shortcutKeysFinished(const QString & shortcutKeys);
    void invalidShortcutKey(const QString & shortcutKeys);

public slots:
    void clearShortcutKey();
    void setShortcutKey(const QString & key);

private slots:
    void toEchoMode();
    void toInputMode() const;
    void shortcutKeyPress(QKeyEvent *e);

private:
    QString convertShortcutKeys(const QString & keys);

private:
    DShortcutEditLabel *m_keysLabel;
    QLabel *m_keysEdit;

    QString m_shortcutKeys;

    static const QString m_defaultTips;
    static const QRegExp m_blockShortcutKeys[];
};

class DShortcutEditLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor echoNormal MEMBER m_colorNormal NOTIFY colorSettingChange DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor echoHover MEMBER m_colorHover NOTIFY colorSettingChange DESIGNABLE true SCRIPTABLE true)
    Q_PROPERTY(QColor echoInvalid MEMBER m_colorInvalid NOTIFY colorSettingChange DESIGNABLE true SCRIPTABLE true)

public:
    enum EchoState {Normal = 1, Hover, Invalid};

public:
    DShortcutEditLabel(QWidget * parent = 0);

    void setEchoState(const EchoState state);

signals:
    void colorSettingChange();

private:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    QColor m_colorNormal;
    QColor m_colorHover;
    QColor m_colorInvalid;

    EchoState m_state = Normal;
};

DUI_END_NAMESPACE

#endif // DSHORTCUTEDIT_H
