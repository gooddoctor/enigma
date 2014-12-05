TEMPLATE = app
TARGET = enigma

QMAKE_CXX = clang++
QMAKE_LINK = clang++
QMAKE_CXXFLAGS += -std=c++11

QT += widgets

INCLUDEPATH += . element /usr/local/include
LIBPATH += /usr/local/lib
LIBS += -lgcrypt -lgpg-error 

include(element/include.inc)
include(function/include.inc)
include(view/include.inc)

SOURCES += main.cpp
