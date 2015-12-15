#include <QRegExpValidator>
#include <QHBoxLayout>
#include <QGuiApplication>
#include <QClipboard>
#include <QKeyEvent>
#include <QDebug>

#include "dthememanager.h"
#include "dipv4lineedit.h"
#include "private/dipv4lineedit_p.h"

DUI_BEGIN_NAMESPACE

DIpv4LineEditPrivate::DIpv4LineEditPrivate(DIpv4LineEdit *parent) :
    DLineEditPrivate(parent)
{

}

void DIpv4LineEditPrivate::init()
{
    D_Q(DIpv4LineEdit);

    editMainWidget = new QWidget(q);

    QHBoxLayout *hbox_layout = new QHBoxLayout;

    hbox_layout->setSpacing(0);
    hbox_layout->setMargin(0);
    hbox_layout->addWidget(getEdit());
    hbox_layout->addWidget(getLabel());
    hbox_layout->addWidget(getEdit());
    hbox_layout->addWidget(getLabel());
    hbox_layout->addWidget(getEdit());
    hbox_layout->addWidget(getLabel());
    hbox_layout->addWidget(getEdit());

    editMainWidget->setLayout(hbox_layout);

    q->DLineEdit::setReadOnly(true);
    q->setFocusProxy(editList.first());

    QObject::connect(q, &DIpv4LineEdit::sizeChanged,
                     editMainWidget, static_cast<void (QWidget::*)(const QSize&)>(&QWidget::resize));

    _q_updateLineEditText();
}

QLabel *DIpv4LineEditPrivate::getLabel()
{
    QLabel *label = new QLabel(".");

    label->setObjectName("DIpv4LineEdit_Label");
    label->setCursor(Qt::IBeamCursor);

    return label;
}

QLineEdit *DIpv4LineEditPrivate::getEdit()
{
    D_Q(DIpv4LineEdit);

    QLineEdit *edit = new QLineEdit;

    edit->setObjectName("DIpv4LineEdit_Edit");
    edit->setValidator(new QRegularExpressionValidator(QRegularExpression("(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)"), edit));
    edit->setAlignment(Qt::AlignHCenter);
    edit->setAttribute(Qt::WA_InputMethodEnabled, false);
    edit->setContextMenuPolicy(Qt::NoContextMenu);
    edit->installEventFilter(q);

    editList << edit;

    QObject::connect(edit, SIGNAL(textChanged(QString)), q, SLOT(_q_updateLineEditText()), Qt::DirectConnection);
    QObject::connect(q, SIGNAL(textChanged(QString)), q, SLOT(_q_setIpLineEditText(QString)), Qt::DirectConnection);

    return edit;
}

void DIpv4LineEditPrivate::_q_updateLineEditText()
{
    if(!enableUpdateLineEditText)
        return;

    D_Q(DIpv4LineEdit);

    QString text;

    for(const QLineEdit *edit : editList) {
        text.append(".").append(edit->text());
    }

    if(enableSetIpLineEditText) {
        enableSetIpLineEditText = false;
        q->setText(text.mid(1));
        enableSetIpLineEditText = true;
    } else {
        q->setText(text.mid(1));
    }

    q->DLineEdit::setCursorPosition(q->cursorPosition());
}

void DIpv4LineEditPrivate::_q_setIpLineEditText(const QString &text)
{
    if(!enableSetIpLineEditText)
        return;

    QRegExp rx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){0,3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)?");

    if(!rx.exactMatch(text)) {
        _q_updateLineEditText();
        return;
    }

    const QStringList text_list = text.split('.');

    int min_count = qMin(editList.count(), text_list.count());

    bool bak_enableUpdateLineEditText = enableSetIpLineEditText;

    for(int i = 0; i < min_count; ++i ) {
        QLineEdit *edit = editList[i];

        enableSetIpLineEditText = false;
        edit->setText(text_list[i]);
        enableSetIpLineEditText = bak_enableUpdateLineEditText;
    }

    for(int i = min_count; i < editList.count(); ++i)
        editList[i]->clear();

    _q_updateLineEditText();
}

DIpv4LineEdit::DIpv4LineEdit(QWidget *parent) :
    DLineEdit(*new DIpv4LineEditPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(DIpv4LineEdit);

    d_func()->init();
}

QString DIpv4LineEdit::displayText() const
{
    return text();
}

int DIpv4LineEdit::cursorPosition() const
{
    D_DC(DIpv4LineEdit);

    int cursorPosition = 0;

    for(const QLineEdit *edit : d->editList) {
        if(edit->hasFocus()) {
            cursorPosition += edit->cursorPosition();
            break;
        } else {
            cursorPosition += edit->text().count() + 1;
        }
    }

    return cursorPosition;
}

Qt::Alignment DIpv4LineEdit::alignment() const
{
    return Qt::AlignHCenter;
}

bool DIpv4LineEdit::hasAcceptableInput() const
{
    D_DC(DIpv4LineEdit);

    bool has = true;

    for(const QLineEdit *edit : d->editList) {
        has = has && edit->hasAcceptableInput();
    }

    return has;
}

bool DIpv4LineEdit::isReadOnly() const
{
    return d_func()->editList.first()->isReadOnly();
}

void DIpv4LineEdit::setCursorPosition(int cursorPosition)
{
    DLineEdit::setCursorPosition(cursorPosition);

    D_D(DIpv4LineEdit);

    for(QLineEdit *edit : d->editList) {
        if(cursorPosition > edit->text().count()) {
            cursorPosition -= edit->text().count();
            --cursorPosition;
        } else {
            edit->setCursorPosition(cursorPosition);
            edit->setFocus();

            break;
        }
    }
}

void DIpv4LineEdit::setReadOnly(bool readOnly)
{
    D_D(DIpv4LineEdit);

    for(QLineEdit *edit : d->editList) {
        edit->setReadOnly(readOnly);
    }
}

void DIpv4LineEdit::setSelection(int start, int length)
{
    D_D(DIpv4LineEdit);

    for(QLineEdit *edit : d->editList) {
        if(edit->text().count() > start) {
            if(edit->text().count() < length + start) {
                int tmp_length = edit->text().count() - start;

                edit->setSelection(start, tmp_length);

                length -= tmp_length;
            } else {
                edit->setSelection(start, length);
                break;
            }
        } else {
            edit->setSelection(edit->cursorPosition(), 0);
        }

        start -= edit->text().count();
    }

    DLineEdit::setSelection(start, length);
}

void DIpv4LineEdit::selectAll()
{
    D_D(DIpv4LineEdit);

    for(QLineEdit *edit : d->editList) {
        edit->selectAll();
    }

    DLineEdit::selectAll();
}

bool DIpv4LineEdit::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::KeyPress) {
        QLineEdit *edit = qobject_cast<QLineEdit*>(obj);

        if(edit) {
            QKeyEvent *event = static_cast<QKeyEvent*>(e);

            if(event) {
                D_D(DIpv4LineEdit);

                if(event->key() == Qt::Key_Backspace) {
                    bool accept = false;

                    for(QLineEdit *edit : d->editList) {
                        if(!edit->selectedText().isEmpty()) {
                            edit->setText(edit->text().remove(edit->selectedText()));
                            accept = true;
                        }
                    }

                    if(accept)
                        return true;
                }

                if(event->key() == Qt::Key_Left
                          || (event->key() == Qt::Key_Backspace
                              && edit->cursorPosition() == 0)) {
                    setCursorPosition(cursorPosition() - 1);

                    return true;
                }

                if(event->key() == Qt::Key_Right) {
                    setCursorPosition(cursorPosition() + 1);

                    return true;
                }

                if(event->key() == Qt::Key_Period || event->key() == Qt::Key_Space) {
                    int index = d->editList.indexOf(edit);

                    if(index < d->editList.count() - 1) {
                        d->editList[index + 1]->setFocus();
                    }

                    return true;
                }

                if(event->modifiers() == Qt::ControlModifier) {
                    if(event->key() == Qt::Key_V) {
                        QString text = qApp->clipboard()->text();

                        QRegExp rx("(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");

                        if(rx.exactMatch(text)) {
                            edit->setText(edit->text().insert(edit->cursorPosition(), text));
                        } else {
                            d->_q_setIpLineEditText(text);
                        }

                        return true;
                    } else if(event->key() == Qt::Key_A) {
                        selectAll();
                    } else if(event->key() == Qt::Key_X) {
                        cut();
                    } else {
                        DLineEdit::keyPressEvent(event);
                    }

                    return true;
                }
            }
        }
    } else if(e->type() == QEvent::FocusIn) {
        QLineEdit *edit = qobject_cast<QLineEdit*>(obj);

        if(edit) {
            DLineEdit::setCursorPosition(cursorPosition());
        }
    } else if(e->type() == QEvent::FocusOut || e->type() == QEvent::MouseButtonPress) {
        D_D(DIpv4LineEdit);

        for(QLineEdit *edit : d->editList) {
            edit->setSelection(edit->cursorPosition(), 0);
        }
    }

    return DLineEdit::eventFilter(obj, e);
}

#include "moc_dipv4lineedit.cpp"

DUI_END_NAMESPACE
