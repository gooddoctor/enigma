TEMPLATE = app
TARGET = enigma

QMAKE_CXX = clang++
QMAKE_LINK = clang++
QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += /usr/local/include
LIBPATH += /usr/local/lib
LIBS += -lgcrypt -lgpg-error 

include(recipe/include.inc)

SOURCES += main.cpp
