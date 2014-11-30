TEMPLATE = app
TARGET = enigma

QMAKE_CXX = clang++
QMAKE_LINK = clang++
QMAKE_CXXFLAGS += -std=c++11

QT += widgets

INCLUDEPATH += . element

include(element/include.inc)

SOURCES += main.cpp
