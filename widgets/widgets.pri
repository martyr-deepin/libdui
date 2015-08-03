include(private/private.pri)

HEADERS += $$PWD/dslider.h\
    $$PWD/dthememanager.h \
    $$PWD/dapplication.h \
    $$PWD/dconstants.h \
    $$PWD/dseparatorhorizontal.h \
    $$PWD/dseparatorvertical.h \
    $$PWD/dbaseline.h \
    $$PWD/dheaderline.h \
    $$PWD/dbaseexpand.h \
    $$PWD/darrowbutton.h \
    $$PWD/darrowlineexpand.h \
    $$PWD/dbuttonlist.h \
    $$PWD/dswitchbutton.h \
    $$PWD/dsegmentedcontrol.h

SOURCES += $$PWD/dslider.cpp \
    $$PWD/dthememanager.cpp \
    $$PWD/dapplication.cpp \
    $$PWD/dseparatorhorizontal.cpp \
    $$PWD/dseparatorvertical.cpp \
    $$PWD/dbaseline.cpp \
    $$PWD/dheaderline.cpp \
    $$PWD/dbaseexpand.cpp \
    $$PWD/darrowbutton.cpp \
    $$PWD/darrowlineexpand.cpp \
    $$PWD/dbuttonlist.cpp \
    $$PWD/dswitchbutton.cpp \
    $$PWD/dsegmentedcontrol.cpp

RESOURCES += \
    $$PWD/../themes/dark.qrc \
    $$PWD/../themes/light.qrc
