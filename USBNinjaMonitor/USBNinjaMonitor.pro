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

LIBS += "..\..\USBNinjaDll\Build\release\libusb32.a" -lboost_system -lboost_thread

DEFINES += BOOST_THREAD_USE_LIB

RC_FILE = versioninfo.rc

HEADERS += \
    handler.h \
    usbops.h \
    main.h \
    traynotify.h

QMAKE_CXXFLAGS += -Wno-write-strings    #Get rid of annoying warnings for const *char to *char

#DEFINES +=  LOG_FILE=\\\"C:/users/grant/desktop/log.db\\\"
#DEFINES +=  AUTH_FILE=\\\"C:/users/grant/desktop/log.db\\\"
#DEFINES +=  ERR_LOG_FILE=\\\"C:/users/grant/desktop/log.txt\\\"
