#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T22:24:56
#
#-------------------------------------------------

QT += qml quick declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UserIdentificationForDicty
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp\
useridentificationmodule.cpp \
    user.cpp

HEADERS  += widget.h \
    useridentificationmodule.h \
    user.h
CONFIG += c++11

RESOURCES += \
    resources.qrc
