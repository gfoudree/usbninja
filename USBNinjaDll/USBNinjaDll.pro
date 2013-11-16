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
    paths.cpp \
    configparser.cpp \
    mysqldb.cpp

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
    paths.h \
    configparser.h \
    mysqldb.h

LIBS += -lboost_random -lz  -lsqlite3 -lpugi -lmysql

OTHER_FILES += \
    versioninfo.rc

RC_FILE = versioninfo.rc

QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE -= -O1

QMAKE_POST_LINK += $$QMAKE_COPY $$quote("debug/"$$TARGET".dll") $$quote("../../USBNinjaMonitor/Build/debug/usb32.dll") \
                   & $$QMAKE_COPY $$quote("debug/"$$TARGET".dll") $$quote("../../USBNinjaGUI/Build/debug/usb32.dll")


QMAKE_CXXFLAGS += -Wno-write-strings #Get rid of annoying warnings for const *char to *char

QMAKE_LFLAGS +=  -static-libstdc++ -static-libgcc
