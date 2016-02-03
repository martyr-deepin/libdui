/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "dheaderline.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DHeaderLine::DHeaderLine(QWidget *parent) : DBaseLine(parent)
{
    D_THEME_INIT_WIDGET(DHeaderLine);

    setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    setFixedHeight(DUI::EXPAND_HEADER_HEIGHT);
    m_titleLabel = new QLabel(this);
    m_titleLabel->setObjectName("DHeaderLineTitle");
    DBaseLine::setLeftContent(m_titleLabel);
}

void DHeaderLine::setTitle(const QString &title)
{
    m_titleLabel->setText(title);
}

void DHeaderLine::setContent(QWidget *content)
{
    DBaseLine::setRightContent(content);
    setFixedHeight(DUI::CONTENT_HEADER_HEIGHT);
}

DUI_END_NAMESPACE
