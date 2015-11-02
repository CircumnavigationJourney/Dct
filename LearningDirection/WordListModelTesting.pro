#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T21:50:06
#
#-------------------------------------------------

QT       += qml quick declarative
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TARGET = WordListModelTesting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    word.cpp \
    wordlist.cpp \
    wordmodel.cpp \
    transcription.cpp \
    translation.cpp \
    reminderdata.cpp \
    testsdata.cpp \
    statisticsdata.cpp \
    partofspeech.cpp \
    wordsortfiltermodel.cpp \
    applicationwindow_test.cpp \
    vocabulary/vocabulary.cpp \
    vocabulary/vocabularylist.cpp \
    vocabulary/vocabularymodel.cpp \
    vocabulary/vocabularyproxymodel.cpp \
    vocabulary/vocabularywidget.cpp \
    wordlistwidget.cpp \
    learningdirection.cpp \
    learningdirectionwidget.cpp

HEADERS  += mainwindow.h \
    word.h \
    wordlist.h \
    wordmodel.h \
    transcription.h \
    translation.h \
    reminderdata.h \
    testsdata.h \
    statisticsdata.h \
    partofspeech.h \
    wordsortfiltermodel.h \
    applicationwindow_test.h \
    vocabulary/vocabulary.h \
    vocabulary/vocabularylist.h \
    vocabulary/vocabularymodel.h \
    vocabulary/vocabularyproxymodel.h \
    vocabulary/vocabularywidget.h \
    wordlistwidget.h \
    learningdirection.h \
    learningdirectionwidget.h \
    langlistiso.h

FORMS    += mainwindow.ui \
    applicationwindow_test.ui \
    vocabulary/vocabularywidget.ui \
    wordlistwidget.ui \
    learningdirectionwidget.ui

RESOURCES += \
    qml.qrc
