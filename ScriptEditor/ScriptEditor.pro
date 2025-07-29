QT += core gui widgets network

CONFIG += c++11 warn_on

# The following define makes your code fail to compile if it uses Qt features
# that have been marked deprecated (the exact warnings depend on your Qt version)
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

TARGET = ScriptEditor
TEMPLATE = app

# Sources
SOURCES += \
    main.cpp \
    scripteditor.cpp

# Headers
HEADERS += \
    scripteditor.h

# Forms
FORMS += \
    scripteditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
