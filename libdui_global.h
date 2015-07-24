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

#endif // LIBDUI_GLOBAL_H
