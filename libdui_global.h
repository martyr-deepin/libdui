#ifndef LIBDUI_GLOBAL_H
#define LIBDUI_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtCore/QMetaMethod>

#if defined(LIBDUI_LIBRARY)
#  define LIBDUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBDUISHARED_EXPORT Q_DECL_IMPORT
#endif

#define DUI_DECL_DEPRECATED Q_DECL_DEPRECATED

#define DUI_NAMESPACE DUI

#if !defined(DUI_NAMESPACE)
#   define DUI_BEGIN_NAMESPACE
#   define DUI_END_NAMESPACE
#   define DUI_USE_NAMESPACE
#else
#   define DUI_BEGIN_NAMESPACE namespace DUI_NAMESPACE {
#   define DUI_END_NAMESPACE }
#   define DUI_USE_NAMESPACE using namespace DUI_NAMESPACE;
#endif

#define D_THEME_INIT_WIDGET(className, propertys...) \
    DThemeManager * manager = DThemeManager::instance(); \
    this->setStyleSheet(this->styleSheet() + manager->getQssForWidget(#className)); \
    connect(manager, &DThemeManager::themeChanged, [=](QString) { \
        this->setStyleSheet(manager->getQssForWidget(#className)); \
    });\
    QStringList list = QString(#propertys).replace(" ", "").split(",");\
    const QMetaObject *self = metaObject();\
    foreach (const QString &str, list) {\
        if(str.isEmpty())\
            continue;\
        connect(this, self->property(self->indexOfProperty(str.toLatin1().data())).notifySignal(),\
        manager, manager->metaObject()->method(manager->metaObject()->indexOfMethod("updateQss()")));\
    }
#endif // LIBDUI_GLOBAL_H
