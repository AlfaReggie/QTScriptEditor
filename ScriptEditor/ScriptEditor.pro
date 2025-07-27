QT += core gui widgets network

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

SOURCES += \
        main.cpp \
        scripteditor.cpp

HEADERS += \
        scripteditor.h

FORMS += \
        scripteditor.ui

target.path = $$[QT_INSTALL_BINS]

INSTALLS += target
