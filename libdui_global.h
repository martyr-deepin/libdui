#ifndef LIBDUI_GLOBAL_H
#define LIBDUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBDUI_LIBRARY)
#  define LIBDUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBDUISHARED_EXPORT Q_DECL_IMPORT
#endif

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

// for D_THEME_INIT_WIDGET macro
#include "widgets/dthememanager.h"

#define D_THEME_INIT_WIDGET(className) \
    DThemeManager * manager = DThemeManager::instance(); \
    this->setStyleSheet(this->styleSheet() + manager->getQssForWidget(#className)); \
    connect(manager, &DThemeManager::themeChanged, [=](QString) { \
        this->setStyleSheet(this->styleSheet() + manager->getQssForWidget(#className)); \
    })

#endif // LIBDUI_GLOBAL_H
