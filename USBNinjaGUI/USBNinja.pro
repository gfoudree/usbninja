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
    authdrive.cpp \
    graphdialog.cpp \
    csvexport.cpp \
    logviewdialog.cpp \
    settingsdialog.cpp \
    usbwizard.cpp \
    daemonstatusdialog.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    managedrivesdialog.h \
    authdrive.h \
    graphdialog.h \
    csvexport.h \
    logviewdialog.h \
    settingsdialog.h \
    usbwizard.h \
    daemonstatusdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    managedrivesdialog.ui \
    authorizedevicedialog.ui \
    graphdialog.ui \
    logviewdialog.ui \
    settingsdialog.ui \
    usbwizard.ui \
    daemonstatusdialog.ui

RC_FILE = versioninfo.rc

QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE -= -O1

QMAKE_LFLAGS += -static -static-libstdc++ -static-libgcc

LIBS += ../../USBNinjaDll/Build/debug/libusb32.a -LC:/MinGW/lib -lcryptopp -lnightcharts
#LIBS += "..\..\USBNinjaDll\Build\release\usb32.dll" -LC:/MinGW/lib -lcryptopp -lnightcharts

OTHER_FILES +=

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -Wno-write-strings -std=c++11 #Get rid of annoying warnings for const *char to *char
