QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../ClientInterface


SOURCES += \
    test_homewindow.cpp \
    test_homewindow.cpp \
    ../ClientInterface/homewindow.cpp \
    ../ClientInterface/equationsolver.cpp

HEADERS += \
    ../ClientInterface/homewindow.h \
    ../ClientInterface/equationsolver.h

FORMS += \
    ../ClientInterface/homewindow.ui
