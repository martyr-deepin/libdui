#ifndef DFILECHOOSEREDIT_H
#define DFILECHOOSEREDIT_H

#include "dlineedit.h"

DUI_BEGIN_NAMESPACE

class DFileChooserEditPrivate;
class LIBDUISHARED_EXPORT DFileChooserEdit : public DLineEdit
{
    Q_OBJECT

    Q_ENUMS(DialogDisplayPosition)
    Q_PROPERTY(DialogDisplayPosition dialogDisplayPosition READ dialogDisplayPosition WRITE setDialogDisplayPosition)

public:
    enum DialogDisplayPosition{
        FoloowParentWindow,
        CurrentMonitorCenter
    };


    DFileChooserEdit(QWidget *parent = nullptr);

    DialogDisplayPosition dialogDisplayPosition() const;

public Q_SLOTS:
    void setDialogDisplayPosition(DialogDisplayPosition dialogDisplayPosition);

Q_SIGNALS:
    void fileChoosed(const QString &fileName);
    void dialogOpened();
    void dialogClosed(int code);

protected:
    Q_DISABLE_COPY(DFileChooserEdit)
    D_DECLARE_PRIVATE(DFileChooserEdit)
    Q_PRIVATE_SLOT(d_func(), void _q_showFileChooserDialog())
};

DUI_END_NAMESPACE

#endif // DFILECHOOSEREDIT_H
