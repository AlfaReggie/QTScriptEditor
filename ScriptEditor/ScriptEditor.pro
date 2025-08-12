QT += core gui widgets network

CONFIG += c++11 warn_on

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

TARGET = ScriptEditor
TEMPLATE = app

SOURCES += \
    main.cpp \
    scripteditor.cpp

HEADERS += \
    scripteditor.h

FORMS += \
    scripteditor.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
