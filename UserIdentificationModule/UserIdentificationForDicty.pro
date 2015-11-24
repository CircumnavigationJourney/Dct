#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T22:24:56
#
#-------------------------------------------------

QT += qml quick declarative concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_FILE = myapp.rc
CONFIG += c++11
TARGET = UserIdentificationForDicty
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp\
useridentificationmodule.cpp \
    user.cpp \
    userlistmodel.cpp \
    useraccountmanager.cpp \
    usersettings.cpp \
    uitheme.cpp \
    uilanguage.cpp

HEADERS  += widget.h \
    useridentificationmodule.h \
    user.h \
    userlistmodel.h \
    useraccountmanager.h \
    usersettings.h \
    uitheme.h \
    uilanguage.h
RESOURCES += \
    resources.qrc
OTHER_FILES += LoginWindow.qml \
DictyQMLComponents/*
DISTFILES += \
    DictyQMLComponents/Button.qml \
    DictyQMLComponents/ButtonStyle.qml
LIBS += -lQt5Concurrent
