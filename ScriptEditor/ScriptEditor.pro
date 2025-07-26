QT += core gui widgets network

CONFIG += c++17

CONFIG += warn_on

CONFIG += release

SOURCES += \
        main.cpp \
        scripteditor.cpp

HEADERS += \
        scripteditor.h

FORMS += \
        scripteditor.ui

target.path = $$[QT_INSTALL_BINS]

INSTALLS += target
