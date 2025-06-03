TEMPLATE = app
CONFIG += console testcase
QT += core network sql testlib

SOURCES += main.cpp \
           C:\Users\timof\OneDrive\Рабочий стол\ТМП\Tech_Prog_2025\Server/mytcpserver.cpp \
           testmytcpserver.cpp \
           C:\Users\timof\OneDrive\Рабочий стол\ТМП\Tech_Prog_2025\Server/equationsolver.cpp

HEADERS += C:\Users\timof\OneDrive\Рабочий стол\ТМП\Tech_Prog_2025\Server/mytcpserver.h \
    testmytcpserver.h \
    C:\Users\timof\OneDrive\Рабочий стол\ТМП\Tech_Prog_2025\Server/equationsolver.h

INCLUDEPATH += C:\Users\timof\OneDrive\Рабочий стол\ТМП\Tech_Prog_2025\Server

TARGET = ServerTests


QT += concurrent
