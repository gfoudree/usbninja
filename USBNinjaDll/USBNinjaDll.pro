TEMPLATE = lib
CONFIG += console
CONFIG -= qt
TARGET = usb32

SOURCES += \
    usbdevice.cpp \
    sql.cpp \
    errorlog.cpp \
    settings.cpp \
    accesslog.cpp \
    service.cpp \
    usbbpb.cpp \
    usbkey.cpp \
    paths.cpp

HEADERS += \
    usbdevice.h \
    sql.h \
    errorlog.h \
    settings.h \
    accesslog.h \
    service.h \
    usbbpb.h \
    usbkey.h \
    bpb.h \
    paths.h

LIBS += -lsqlite3 -lpugi -lz -lboost_random

OTHER_FILES += \
    versioninfo.rc

RC_FILE = versioninfo.rc

#QMAKE_POST_LINK += $$QMAKE_COPY $$quote("debug/"$$TARGET".dll") $$quote("../../USBNinjaMonitor/Build/debug/usb32.dll") \
#                   & $$QMAKE_COPY $$quote("debug/"$$TARGET".dll") $$quote("../../USBNinjaGUI/Build/debug/usb32.dll")


QMAKE_CXXFLAGS += -Wno-write-strings -g #Get rid of annoying warnings for const *char to *char

QMAKE_LFLAGS += -static -static-libstdc++ -static-libgcc

#DEFINES +=  LOG_FILE=\\\"C:/users/grant/desktop/log.db\\\"
#DEFINES +=  AUTH_FILE=\\\"C:/users/grant/desktop/log.db\\\"
#DEFINES +=  ERR_LOG_FILE=\\\"C:/users/grant/desktop/log.txt\\\"
