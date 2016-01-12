#ifndef DOPTION_P_H
#define DOPTION_P_H

#include "doption.h"
#include "dobject_p.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QListWidgetItem>

DUI_BEGIN_NAMESPACE

class DOptionPrivate : public DObjectPrivate
{
    D_DECLARE_PUBLIC(DOption)

public:
    DOptionPrivate(DOption *q);

    void init();

    void setIcon(const QString& iconName);
    void setIcon(const QPixmap& icon);

    const QString name() const;
    const QString value() const;

    bool checked() const;
    void setChecked(bool checked);

    const QString checkedIcon() const;
    void setCheckedIcon(const QString &icon);

    void sizeChanged(QResizeEvent *e);

public slots:
    void _q_itemStateChanged(QListWidgetItem* item);

public:
    bool m_checked = false;
    QString m_optionValue;
    QString m_checkedIconName;

    QLabel *m_checkedIconLabel;
    QLabel *m_optionIcon;
    QLabel *m_optionName;

    QHBoxLayout *m_layout;
};

DUI_END_NAMESPACE

#endif // DOPTION_P_H

