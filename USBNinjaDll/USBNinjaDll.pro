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
    service.cpp

HEADERS += \
    usbdevice.h \
    sql.h \
    errorlog.h \
    settings.h \
    accesslog.h \
    service.h

LIBS += -lsqlite3 -lpugi

OTHER_FILES += \
    versioninfo.rc

RC_FILE = versioninfo.rc

QMAKE_POST_LINK += $$QMAKE_COPY $$quote("debug/"$$TARGET".dll") $$quote("../../USBNinjaMonitor/Build/debug/usb32.dll") \
                   & $$QMAKE_COPY $$quote("debug/"$$TARGET".dll") $$quote("../../USBNinjaGUI/Build/debug/usb32.dll")


QMAKE_CXXFLAGS += -Wno-write-strings   #Get rid of annoying warnings for const *char to *char

QMAKE_LFLAGS += -static -static-libstdc++ -static-libgcc
