#ifndef LIBDUI_GLOBAL_H
#define LIBDUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBDUI_LIBRARY)
#  define LIBDUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBDUISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBDUI_GLOBAL_H
