#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T19:24:36
#
#-------------------------------------------------

include(widgets/widgets.pri)

QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dui
VERSION = 1.0
TEMPLATE = lib

DEFINES += LIBDUI_LIBRARY

CONFIG += c++11 create_pc create_prl no_install_prl

HEADERS += libdui_global.h

isEmpty(LIB_INSTALL_DIR) {
    target.path = /usr/lib
} else {
    target.path = $$LIB_INSTALL_DIR
}

includes.files += libdui_global.h widgets/*.h
includes.path = /usr/include/libdui/

unix{
    QT += x11extras dbus
    INSTALLS += includes target
}

QMAKE_PKGCONFIG_NAME = DUI
QMAKE_PKGCONFIG_DESCRIPTION = Deepin UI in Qt
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$includes.path
QMAKE_PKGCONFIG_VERSION = $$VERSION
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
