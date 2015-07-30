#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T19:24:36
#
#-------------------------------------------------

QT       += widgets

TARGET = dui
VERSION = 1.0
TEMPLATE = lib

DEFINES += LIBDUI_LIBRARY

CONFIG += c++11

include(widgets/widgets.pri)

HEADERS += libdui_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target

    includes.files += libdui_global.h widgets/*.h
    includes.path = /usr/include/libdui/

    INSTALLS += includes
}
