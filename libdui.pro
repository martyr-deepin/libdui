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
    widgets/dapplication.cpp \
    widgets/dsegmentedcontrol.cpp
    widgets/dseparatorhorizontal.cpp \
    widgets/dseparatorvertical.cpp \
    widgets/dbaseline.cpp \
    widgets/dheaderline.cpp \
    widgets/dbaseexpand.cpp \
    widgets/private/dthemehelper.cpp \
    widgets/darrowbutton.cpp \
    widgets/darrowlineexpand.cpp

HEADERS += widgets/dslider.h\
        libdui_global.h \
    widgets/dthememanager.h \
    widgets/dapplication.h \
    widgets/dsegmentedcontrol.h
    widgets/dconstants.h \
    widgets/dseparatorhorizontal.h \
    widgets/dseparatorvertical.h \
    widgets/dbaseline.h \
    widgets/dheaderline.h \
    widgets/dbaseexpand.h \
    widgets/private/dthemehelper.h \
    widgets/darrowbutton.h \
    widgets/darrowlineexpand.h

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
