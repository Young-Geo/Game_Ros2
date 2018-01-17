TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../Ybasis
INCLUDEPATH += /home/anxan/ros2_ws/install/include


TARGET = Node_DB

SOURCES += \
    src/mian.cpp \
    src/main.cpp
