/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DBOXWIDGET_P_H
#define DBOXWIDGET_P_H

#include "dobject_p.h"
#include "dboxwidget.h"

class QBoxLayout;

DUI_BEGIN_NAMESPACE

class DBoxWidgetPrivate : public DObjectPrivate
{
    DBoxWidgetPrivate(DBoxWidget *qq);

    QBoxLayout *layout;

    void init();

    Q_DECLARE_PUBLIC(DBoxWidget)
};

DUI_END_NAMESPACE

#endif // DBOXWIDGET_P_H

