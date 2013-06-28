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
        mainwindow.cpp \
    aboutdialog.cpp \
    managedrivesdialog.cpp \
    authorizedevicedialog.cpp \
    authdrive.cpp \
    graphdialog.cpp \
    csvexport.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    managedrivesdialog.h \
    authorizedevicedialog.h \
    authdrive.h \
    graphdialog.h \
    csvexport.h \
    SerialStamp.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    managedrivesdialog.ui \
    authorizedevicedialog.ui \
    graphdialog.ui

RC_FILE = versioninfo.rc

QMAKE_LFLAGS += -static -static-libstdc++ -static-libgcc

LIBS += "..\..\USBNinjaDll\Build\debug\libusb32.a" -lcryptopp -lnightcharts

OTHER_FILES +=

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -Wno-write-strings -g #Get rid of annoying warnings for const *char to *char

DEFINES +=  LOG_FILE=\\\"C:/users/grant/desktop/log.db\\\"
DEFINES +=  AUTH_FILE=\\\"C:/users/grant/desktop/log.db\\\"
