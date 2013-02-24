#-------------------------------------------------
#
# Project created by QtCreator 2013-01-19T23:48:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USBNinjaGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RC_FILE = versioninfo.rc

QMAKE_LFLAGS += -static -static-libstdc++ -static-libgcc

LIBS += "..\..\USBNinjaDll\Build\debug\libusb32.a"

OTHER_FILES +=

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -Wno-write-strings    #Get rid of annoying warnings for const *char to *char
