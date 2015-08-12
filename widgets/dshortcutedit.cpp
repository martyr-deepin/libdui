#include "dshortcutedit.h"
#include "dthememanager.h"

#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

#include <cctype>

DUI_USE_NAMESPACE

// static const varibles
const QString DShortcutEdit::m_defaultTips = tr("请输入新的快捷键");
const QRegExp DShortcutEdit::m_blockShortcutKeys[] = {QRegExp("^Backspace$")};

DShortcutEdit::DShortcutEdit(QWidget *parent)
    : QFrame(parent)
{
    D_THEME_INIT_WIDGET(DShortcutEdit);

    m_keysEdit = new QLabel(m_defaultTips);
    m_keysEdit->setObjectName("Edit");
    m_keysEdit->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    m_keysEdit->installEventFilter(this);
    m_keysEdit->setFocusPolicy(Qt::StrongFocus);
    m_keysEdit->hide();

    m_keysLabel = new DShortcutEditLabel;
    m_keysLabel->setObjectName("Label");
    m_keysLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    m_keysLabel->installEventFilter(this);
    m_keysLabel->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_keysEdit);
    layout->addWidget(m_keysLabel);
    layout->setSpacing(0);
    layout->setMargin(0);

    setLayout(layout);
    setFocusPolicy(Qt::NoFocus);
    // Meta+Ctrl+Alt+Shift+Backspace is longest shortcut keys
    setMinimumWidth(180);
#ifdef QT_DEBUG // for test
    setShortcutKey("Meta+Ctrl+Alt+Shift+Backspace");
#endif

    connect(this, &DShortcutEdit::invalidShortcutKey, [this] () -> void {m_keysLabel->setEchoState(DShortcutEditLabel::Invalid);});
}

bool DShortcutEdit::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_keysEdit && e->type() == QEvent::FocusOut && m_keysEdit->isVisible())
        toEchoMode();
    else if (o == m_keysLabel && e->type() == QEvent::MouseButtonRelease && m_keysLabel->isVisible())
        toInputMode();
    else if (o == m_keysEdit && e->type() == QEvent::KeyPress)
        shortcutKeyPress(static_cast<QKeyEvent *>(e));

    return false;
}

void DShortcutEdit::clearShortcutKey()
{
    setShortcutKey(QString());
}

QSize DShortcutEdit::sizeHint() const
{
    if (!m_keysLabel || !m_keysEdit)
        return QSize();

    return QSize(qMax(m_keysLabel->sizeHint().width(), m_keysEdit->sizeHint().width()),
                 qMax(m_keysLabel->sizeHint().height(), m_keysEdit->sizeHint().height()));
}

void DShortcutEdit::setShortcutKey(const QString &key)
{
    if (key.isEmpty())
        m_keysLabel->setText(tr("无"));
    else
        m_keysLabel->setText(convertShortcutKeys(key));
    m_keysEdit->setText(convertShortcutKeys(key));
    m_shortcutKeys = key;

    emit shortcutKeysChanged(m_shortcutKeys);
}

bool DShortcutEdit::isValidShortcutKey(const QString &key)
{
    for (const QRegExp & k : m_blockShortcutKeys)
        if (key.contains(k))
            return false;

    const QStringList keys = key.split("+");

    if (keys.size() == 1)
    {
        const QString firstKey = keys.first();
        // F1 ~ F12
        if (!firstKey.contains(QRegExp("^F(\\d|1[0-2])$")))
            return false;
    }

    const QString lastKey = keys.last();
    if (lastKey.size() == 2 && !lastKey.at(0).isLetter())
        return false;
    if (lastKey == "Meta" || lastKey == "Ctrl" ||
        lastKey == "Shift" || lastKey == "Alt")
        return false;


    qWarning() << "isValidShortcutKey: " << key;
    return true;
}

void DShortcutEdit::toEchoMode()
{
    m_keysLabel->show();
    m_keysEdit->hide();

    emit shortcutKeysFinished(m_shortcutKeys);

    if (!m_shortcutKeys.isEmpty() && !isValidShortcutKey(m_shortcutKeys))
        emit invalidShortcutKey(m_shortcutKeys);
}

void DShortcutEdit::toInputMode() const
{
    m_keysLabel->hide();
    m_keysLabel->setEchoState(DShortcutEditLabel::Normal);
    m_keysEdit->show();
    m_keysEdit->setFocus();
    m_keysEdit->setText(m_defaultTips);
}

void DShortcutEdit::shortcutKeyPress(QKeyEvent *e)
{
    //qDebug() << e->key() << e->text() << e->count() << Qt::CTRL << e->nativeScanCode() << e->nativeVirtualKey();
    m_shortcutKeys.clear();

    int state = 0;
    if ((e->modifiers() & Qt::ShiftModifier) && (e->text().isEmpty() ||
                                                 !e->text().at(0).isPrint() ||
                                                 e->text().at(0).isLetterOrNumber() ||
                                                 e->text().at(0).isSpace()))
        state |= Qt::SHIFT;
    if (e->modifiers() & Qt::ControlModifier)
        state |= Qt::CTRL;
    if (e->modifiers() & Qt::MetaModifier)
        state |= Qt::META;
    if (e->modifiers() & Qt::AltModifier)
        state |= Qt::ALT;

    int key = e->key() | state;
    qDebug() << "keys: " << QKeySequence(key, 0, 0, 0).toString(QKeySequence::NativeText);
    m_shortcutKeys = QKeySequence(key, 0, 0, 0).toString(QKeySequence::NativeText);

    //qDebug() << m_shortcutKeys << e->text() << e->key();
    //qDebug() << "keys: " << int(e->key() & ~(Qt::SHIFT | Qt::ControlModifier | Qt::META | Qt::ALT));

    // if pressed key is "Backspace", its means "clear all"
    if (m_shortcutKeys == "Backspace")
        return clearShortcutKey();

    setShortcutKey(m_shortcutKeys);

    QString lastKey = m_shortcutKeys.split("+").last();
    qDebug() << "last: " << lastKey << lastKey.size();

    // if lastKey is not alt, shift, ctrl, meta, shortcut key is finished.
    if (lastKey.size() == 2 && !lastKey.at(0).isLetter())
        return;
    if (lastKey != "Meta" && lastKey != "Ctrl" &&
        lastKey != "Shift" && lastKey != "Alt")
        toEchoMode();
}

QString DShortcutEdit::convertShortcutKeys(const QString &keys)
{
    QString newKeys = keys;

    newKeys.replace("PgDown", "PageDown");
    newKeys.replace("PgUp", "PageUp");

    return std::move(newKeys);
}

DShortcutEditLabel::DShortcutEditLabel(QWidget *parent)
    : QLabel(parent)
{
    setEchoState(Normal);

    connect(this, &DShortcutEditLabel::colorSettingChange, [this] () -> void {setEchoState(m_state);});
}

void DShortcutEditLabel::setEchoState(const DShortcutEditLabel::EchoState state)
{
    QColor c = m_colorNormal;

    switch (state)
    {
    case Normal:    c = m_colorNormal;    break;
    case Hover:     c = m_colorHover;     break;
    case Invalid:   c = m_colorInvalid;   break;
    default:        c = m_colorNormal;    break;
    }

    setStyleSheet(QString("color:%1;").arg(c.name()));
    update();

    m_state = state;
}

void DShortcutEditLabel::enterEvent(QEvent *)
{
    if (m_state == Normal)
        setEchoState(Hover);
}

void DShortcutEditLabel::leaveEvent(QEvent *)
{
    if (m_state == Hover)
        setEchoState(Normal);
}
