QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../ClientInterface

SOURCES += \
    test_homewindow.cpp \
    test_homewindow.cpp \
    ../ClientInterface/homewindow.cpp

HEADERS += \
    ../ClientInterface/homewindow.h

FORMS += \
    ../ClientInterface/homewindow.ui
