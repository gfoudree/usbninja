TEMPLATE = lib
CONFIG += console
CONFIG -= qt
TARGET = usb32

SOURCES += \
    usbdevice.cpp \
    sql.cpp \
    errorlog.cpp \
    settings.cpp

HEADERS += \
    usbdevice.h \
    sql.h \
    errorlog.h \
    settings.h

LIBS += -lsqlite3 -lpugi

OTHER_FILES += \
    versioninfo.rc

RC_FILE = versioninfo.rc

QMAKE_POST_LINK += $$QMAKE_COPY $$quote("debug/"$$TARGET".dll") $$quote(../../USBNinjaMonitor/Build/debug/usb32.dll)
