QT += core gui widgets testlib

CONFIG += c++17 console
TEMPLATE = app
TARGET = tst_first

# Подключаем твои файлы
INCLUDEPATH += ../../../ClientInterface

SOURCES += \
    tst_first.cpp \
    ../../../ClientInterface/homewindow.cpp

HEADERS += \
    ../../../ClientInterface/homewindow.h

FORMS += \
    ../../../ClientInterface/homewindow.ui
