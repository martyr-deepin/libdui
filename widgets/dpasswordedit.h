#ifndef DPASSWORDEDIT_H
#define DPASSWORDEDIT_H

#include <QWidget>
#include <QSize>
#include <QPixmap>

#include "dimagebutton.h"
#include "dlineedit.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DPasswordEdit : public QWidget
{
    Q_OBJECT

public:
    explicit DPasswordEdit(QWidget *parent = 0);

public slots:
    void setNormalIcon(const QPixmap & icon) {m_btn.setNormalPic(icon);}
    void setHoverIcon(const QPixmap & icon) {m_btn.setHoverPic(icon);}
    void setShowPasswordIcon(const QPixmap &icon) {m_btn.setCheckedPic(icon);}
    void setPassword(const QString & password) {m_edit.setText(password);}

private:
    DLineEdit m_edit;
    DUI::DImageButton m_btn;
};

DUI_END_NAMESPACE

#endif // DPASSWORDEDIT_H
