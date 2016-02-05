/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include <QDebug>

#include "dapplication.h"
#include "dthememanager.h"
#include "private/dthemehelper.h"
#include "private/dapplication_p.h"

#include <sys/file.h>
#include <unistd.h>

DUI_BEGIN_NAMESPACE

DApplicationPrivate::DApplicationPrivate(DApplication *q) :
    DObjectPrivate(q)
{
}

DApplicationPrivate::~DApplicationPrivate()
{
//    if (m_pidLockFD)
//        close(m_pidLockFD);
}

QString DApplicationPrivate::theme() const
{
    return DThemeManager::instance()->theme();
}

void DApplicationPrivate::setTheme(const QString &theme)
{
    DThemeManager *themeManager = DThemeManager::instance();
    themeManager->setTheme(theme);
}

bool DApplicationPrivate::setSingleInstance(const QString &key)
{
//    const QString file = QString("/run/user/%1/deepin/%2.pid").arg(getuid())
//                                                              .arg(key);


//    m_pidLockFD = open(file.toStdString().c_str(), O_CREAT | O_RDWR, 0600);
//    int rc = flock(m_pidLockFD, LOCK_EX | LOCK_NB);

//    // another instance is running
//    if (rc) {
//        m_pidLockFD = 0;
//        return false;
//    }

//    return true;

    D_Q(DApplication);

    if (!m_socketLock)
        m_socketLock = new QLocalServer(q);

    return m_socketLock->listen(key);
}

DApplication::DApplication(int &argc, char **argv) :
    QApplication(argc, argv),
    DObject(*new DApplicationPrivate(this))
{

}

QString DApplication::theme() const
{
    D_DC(DApplication);

    return d->theme();
}

void DApplication::setTheme(const QString & theme)
{
    D_D(DApplication);

    d->setTheme(theme);
}

bool DApplication::setSingleInstance(const QString &key)
{
    D_D(DApplication);

    return d->setSingleInstance(key);
}

DUI_END_NAMESPACE
