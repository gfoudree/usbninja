TEMPLATE = app
CONFIG += console
CONFIG -= qt
TARGET = usbd

SOURCES += main.cpp \
    handler.cpp \
    usbops.cpp \
    traynotify.cpp

OTHER_FILES += \
    versioninfo.rc

LIBS += "..\..\USBNinjaDll\Build\debug\libusb32.a" -lboost_system -lboost_thread
#LIBS += "..\..\USBNinjaDll\Build\release\usb32.dll" -lboost_system -lboost_thread

DEFINES += BOOST_THREAD_USE_LIB

RC_FILE = versioninfo.rc

HEADERS += \
    handler.h \
    usbops.h \
    main.h \
    traynotify.h

QMAKE_CXXFLAGS += -Wno-write-strings    #Get rid of annoying warnings for const *char to *char
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE -= -O1

QMAKE_LFLAGS +=  -static-libstdc++ -static-libgcc

