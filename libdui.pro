#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T19:24:36
#
#-------------------------------------------------

QT       += widgets dbus

TARGET = dui
VERSION = 1.0
TEMPLATE = lib

DEFINES += LIBDUI_LIBRARY

CONFIG += c++11

include(widgets/widgets.pri)

HEADERS += libdui_global.h

unix {
    isEmpty(LIB_INSTALL_DIR) {
		target.path = /usr/lib
	} else {
		target.path = $$LIB_INSTALL_DIR
	}
    INSTALLS += target

    includes.files += libdui_global.h widgets/*.h
    includes.path = /usr/include/libdui/

    INSTALLS += includes
}

DISTFILES += \
    themes/DButtonGrid.theme

RESOURCES +=
