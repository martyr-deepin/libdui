#ifndef DIPV4LINEEDIT_H
#define DIPV4LINEEDIT_H

#include "dlineedit.h"

DUI_BEGIN_NAMESPACE

class DIpv4LineEditPrivate;
class DIpv4LineEdit : public DLineEdit
{
    Q_OBJECT

    Q_PROPERTY(QString displayText READ displayText)
    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition)
    Q_PROPERTY(Qt::Alignment alignment READ alignment)
    Q_PROPERTY(QString selectedText READ selectedText)
    Q_PROPERTY(bool acceptableInput READ hasAcceptableInput)
    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
    Q_PROPERTY(QString placeholderText READ placeholderText)
    Q_PROPERTY(bool clearButtonEnabled READ isClearButtonEnabled)

public:
    explicit DIpv4LineEdit(QWidget *parent = 0);

    QString displayText() const;
    int cursorPosition() const;
    Qt::Alignment alignment() const;
    QString selectedText() const;
    bool hasAcceptableInput() const;
    bool isReadOnly() const;

public slots:
    void setCursorPosition(int cursorPosition);
    void setReadOnly(bool readOnly);

protected:
    bool eventFilter(QObject *obj, QEvent *e) Q_DECL_OVERRIDE;

private:
    void setPlaceholderText(QString placeholderText);
    void setClearButtonEnabled(bool clearButtonEnabled);

    D_DECLARE_PRIVATE(DIpv4LineEdit)

    Q_PRIVATE_SLOT(d_func(), void _q_updateLineEditText())
    Q_PRIVATE_SLOT(d_func(), void _q_setIpLineEditText(const QString &))
};

DUI_END_NAMESPACE

#endif // DIPV4LINEEDIT_H
