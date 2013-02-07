TEMPLATE = app
CONFIG += console
CONFIG -= qt
TARGET = usbd

SOURCES += main.cpp

OTHER_FILES += \
    versioninfo.rc

LIBS += "..\..\USBNinjaDll\Build\debug\libusb32.a"

RC_FILE = versioninfo.rc
