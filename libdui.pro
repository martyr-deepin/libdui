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

SOURCES += widgets/dslider.cpp \
    widgets/dthememanager.cpp \
    widgets/dapplication.cpp

HEADERS += widgets/dslider.h\
        libdui_global.h \
    widgets/dthememanager.h \
    widgets/dapplication.h

unix {
    target.path = /usr/lib
    INSTALLS += target

    includes.files += libdui_global.h widgets/*.h
    includes.path = /usr/include/libdui/

    INSTALLS += includes
}

RESOURCES += \
    themes/dark.qrc \
    themes/light.qrc
