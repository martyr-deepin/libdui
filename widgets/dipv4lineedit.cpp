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

    q->setAttribute(Qt::WA_InputMethodEnabled, false);
    q->DLineEdit::setReadOnly(true);

    QObject::connect(q, &DIpv4LineEdit::sizeChanged,
                     editMainWidget, static_cast<void (QWidget::*)(const QSize&)>(&QWidget::resize));
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
    edit->installEventFilter(q);

    editList << edit;

    QObject::connect(edit, SIGNAL(textChanged(QString)), q, SLOT(_q_updateLineEditText()));
    QObject::connect(q, SIGNAL(textChanged(QString)), q, SLOT(_q_setIpLineEditText(QString)));

    return edit;
}

void DIpv4LineEditPrivate::_q_updateLineEditText()
{
    D_Q(DIpv4LineEdit);

    QString text;

    for(const QLineEdit *edit : editList) {
        if(!edit->text().isEmpty())
            text.append(edit->text()).append(".");
    }

    this->text = text.left(text.count() - 1);

    q->setText(this->text);
}

void DIpv4LineEditPrivate::_q_setIpLineEditText(const QString &text)
{
    if(text == this->text)
        return;

    const QStringList text_list = text.split('.');

    int max_count = qMin(editList.count(), text_list.count());

    for(int i = 0; i < max_count; ++i ) {
        QLineEdit *edit = editList[i];

        edit->setText(text_list[i]);
    }
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

    int pos;

    for(const QLineEdit *edit : d->editList) {
        pos += edit->cursorPosition();
    }

    return pos;
}

Qt::Alignment DIpv4LineEdit::alignment() const
{
    return Qt::AlignHCenter;
}

QString DIpv4LineEdit::selectedText() const
{
    D_DC(DIpv4LineEdit);

    for(const QLineEdit *edit : d->editList) {
        if(!edit->selectedText().isEmpty())
            return edit->selectedText();
    }

    return "";
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
    D_D(DIpv4LineEdit);

    for(QLineEdit *edit : d->editList) {
        if(cursorPosition > edit->text().count()) {
            cursorPosition -= edit->text().count();
        } else {
            edit->setCursorPosition(cursorPosition);
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

bool DIpv4LineEdit::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::KeyPress) {
        QLineEdit *edit = qobject_cast<QLineEdit*>(obj);

        if(edit) {
            QKeyEvent *event = static_cast<QKeyEvent*>(e);

            if(event) {
                D_D(DIpv4LineEdit);

                if(event->key() == Qt::Key_Backspace) {
                    if(edit->text().count() == 0 && d->editList.indexOf(edit) > 0) {
                        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Tab, Qt::ShiftModifier);
                        qApp->postEvent(edit, event);
                    }
                } else if(event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier) {
                    event->accept();

                    d->_q_setIpLineEditText(qApp->clipboard()->text());

                    return true;
                } else if(event->key() == Qt::Key_Left) {
                    if(edit->cursorPosition() == 0) {
                        int index = d->editList.indexOf(edit) - 1;

                        if(index >= 0) {
                            QLineEdit *left_edit = d->editList[index];

                            left_edit->setFocus();
                            left_edit->setCursorPosition(left_edit->text().count());
                        }
                    }
                } else if(event->key() == Qt::Key_Right) {
                    if(edit->cursorPosition() == edit->text().count()) {
                        int index = d->editList.indexOf(edit) + 1;

                        if(index < d->editList.count()) {
                            QLineEdit *left_edit = d->editList[index];

                            left_edit->setFocus();
                            left_edit->setCursorPosition(0);
                        }
                    }
                }
            }
        }
    }

    return DLineEdit::eventFilter(obj, e);
}

#include "moc_dipv4lineedit.cpp"

DUI_END_NAMESPACE
