#ifndef DCOMBOBOX_P_H
#define DCOMBOBOX_P_H

#include "dobject_p.h"
#include "dcombobox.h"

DUI_BEGIN_NAMESPACE

class DComboBoxPrivate : public DObjectPrivate
{
    DComboBoxPrivate(DComboBox *parent);

    void init();
    void initInsideFrame();

    void _q_slotCurrentIndexChange(int index);

    QLabel *maskLabel = NULL;    //mask label

    QString normalTickImg = "";
    QString hoverTickImg = "";
    QString insensitiveTickImg = "";
    bool alert = false;

    const int MAX_VISIBLE_ITEMS = 16;
    const int OUTSIDE_BORDER_WIDTH = 1;

    D_DECLARE_PUBLIC(DComboBox)
};

DUI_END_NAMESPACE

#endif // DCOMBOBOX_P_H

