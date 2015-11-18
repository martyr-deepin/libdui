#ifndef DFILECHOOSEREDIT_H
#define DFILECHOOSEREDIT_H

#include "dlineedit.h"

DUI_BEGIN_NAMESPACE

class DFileChooserEditPrivate;
class LIBDUISHARED_EXPORT DFileChooserEdit : public DLineEdit
{
    Q_OBJECT
    Q_DISABLE_COPY(DFileChooserEdit)
    D_DECLARE_PRIVATE(DFileChooserEdit)

public:
    DFileChooserEdit(QWidget *parent = nullptr);

Q_SIGNALS:
    void fileChoosed(const QString &fileName);

protected:
    Q_PRIVATE_SLOT(d_func(), void _q_showFileChooserDialog())
};

DUI_END_NAMESPACE

#endif // DFILECHOOSEREDIT_H
