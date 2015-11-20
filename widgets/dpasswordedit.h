#ifndef DPASSWORDEDIT_H
#define DPASSWORDEDIT_H

#include "dlineedit.h"

DUI_BEGIN_NAMESPACE

class DPasswordEditPrivate;
class LIBDUISHARED_EXPORT DPasswordEdit : public DLineEdit
{
    Q_OBJECT
    Q_PROPERTY(bool isEchoMode READ isEchoMode)

public:
    DPasswordEdit(QWidget *parent = nullptr);

    bool isEchoMode() const;
    void setEchoMode(EchoMode mode);

protected:
    Q_DISABLE_COPY(DPasswordEdit)
    D_DECLARE_PRIVATE(DPasswordEdit)
    Q_PRIVATE_SLOT(d_func(), void _q_toggleEchoMode())
};

DUI_END_NAMESPACE

#endif // DPASSWORDEDIT_H
