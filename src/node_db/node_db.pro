TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../Ybasis
INCLUDEPATH += /home/anxan/ros2_ws/install/include


TARGET = Node_DB

SOURCES += \
    src/DBconfig.cpp \
    src/DBYS.cpp \
    src/main.cpp \
    src/ocicursor.cpp \
    src/ocidatabase.cpp \
    src/work.cpp

HEADERS += \
    src/DBconfig.h \
    src/DBYS.h \
    src/ocicursor.h \
    src/ocidatabase.h \
    src/work.h
