QT += core gui widgets network

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated Qt Functions

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
        main.cpp \
        scripteditor.cpp

HEADERS += \
        scripteditor.h

FORMS += \
        scripteditor.ui

#Default rules for development.

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin

!isEmpty(target.path):INSTALL += target
