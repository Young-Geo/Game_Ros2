TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
TARGET = ../Ybasis
INCLUDEPATH += /home/anxan/ros2_ws/install/include
LIBS += -lmsgpack
HEADERS += \
    Ybasis.h \
    Ywork.h \
    Ylog.h \
    Yalone.hpp \
    Ytime.h \
    Yconfig.h \
    YS.h \
    Ysocket.h \
    Ymsgtool.h \
    Ypackage.h \
    Ychain.hpp \
    YSocketClient.h \
    Yuser.h \
    Ynode.hpp

SOURCES += \
    Ywork.cpp \
    Ylog.cpp \
    Ytime.cpp \
    Yconfig.cpp \
    YS.cpp \
    Ysocket.cpp \
    Ymsgtool.cpp \
    Ypackage.cpp \
    YSocketClient.cpp \
    Yuser.cpp \
    Ybasis.cpp
