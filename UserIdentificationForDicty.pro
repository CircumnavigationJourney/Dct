#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T22:24:56
#
#-------------------------------------------------

QT += qml quick declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = UserIdentificationForDicty
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp\
useridentificationmodule.cpp \
    user.cpp \
    userlistmodel.cpp

HEADERS  += widget.h \
    useridentificationmodule.h \
    user.h \
    userlistmodel.h
RESOURCES += \
    resources.qrc
OTHER_FILES += LoginWindow.qml \
DictyQMLComponents/*
DISTFILES += \
    DictyQMLComponents/Button.qml \
    DictyQMLComponents/ButtonStyle.qml
