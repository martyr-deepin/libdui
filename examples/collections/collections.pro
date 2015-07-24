QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = collections
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

LIBS += -ldui
