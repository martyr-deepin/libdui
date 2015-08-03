QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = collections
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$(_PRO_FILE_PWD_)../../ $$(_PRO_FILE_PWD_)../../widgets
include($$(_PRO_FILE_PWD_)../../widgets/widgets.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    buttontab.cpp \
    linetab.cpp \
    bartab.cpp \
    inputtab.cpp \
    slidertab.cpp \
    buttonlisttab.cpp \
    segmentedcontrol.cpp\
    indicatortab.cpp

HEADERS  += mainwindow.h \
    buttontab.h \
    linetab.h \
    bartab.h \
    inputtab.h \
    slidertab.h \
    buttonlisttab.h \
    segmentedcontrol.h \
    indicatortab.h

RESOURCES += \
    images.qrc
