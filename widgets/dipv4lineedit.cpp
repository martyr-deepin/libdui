#include <QRegExpValidator>
#include <QDebug>

#include "dipv4lineedit.h"

DUI_BEGIN_NAMESPACE

DIpv4LineEdit::DIpv4LineEdit(QWidget *parent) :
    DLineEdit(parent)
{
    setAttribute(Qt::WA_InputMethodEnabled, false);
    setValidator(new QRegExpValidator(QRegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}"
                                              "(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)"), this));
    setInputMask("999.999.999.999;0");
}

DUI_END_NAMESPACE
