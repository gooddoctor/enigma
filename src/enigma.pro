TEMPLATE = app
TARGET = enigma

QMAKE_CXX = clang++
QMAKE_LINK = clang++
QMAKE_CXXFLAGS += -std=c++11

include(recipe/include.inc)


# entry point
SOURCES += main.cpp
