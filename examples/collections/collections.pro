QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = collections
TEMPLATE = app
CONFIG += c++11

unix{
    QT += x11extras dbus

    CONFIG += link_pkgconfig
    PKGCONFIG += xext
}

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
    indicatortab.cpp \
    widgetstab.cpp \
    comboboxtab.cpp \
    buttongridtab.cpp \
    imagebuttongridtab.cpp \
    cameraform.cpp \
    graphicseffecttab.cpp \
    flowwidgetlisttab.cpp

HEADERS  += mainwindow.h \
    buttontab.h \
    linetab.h \
    bartab.h \
    inputtab.h \
    slidertab.h \
    buttonlisttab.h \
    segmentedcontrol.h \
    indicatortab.h \
    widgetstab.h \
    comboboxtab.h \
    buttongridtab.h \
    imagebuttongridtab.h \
    cameraform.h \
    graphicseffecttab.h \
    flowwidgetlisttab.h

RESOURCES += \
    images.qrc

FORMS += \
    cameraform.ui
