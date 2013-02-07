TEMPLATE = app
CONFIG += console
CONFIG -= qt
TARGET = usbd

SOURCES += main.cpp \
    handler.cpp \
    usbops.cpp

OTHER_FILES += \
    versioninfo.rc

LIBS += "..\..\USBNinjaDll\Build\debug\libusb32.a" -lboost_system -lboost_thread
DEFINES += BOOST_THREAD_USE_LIB

RC_FILE = versioninfo.rc

HEADERS += \
    handler.h \
    usbops.h
