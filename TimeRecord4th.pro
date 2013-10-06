#-------------------------------------------------
#
# Project created by QtCreator 2013-09-16T09:30:53
#
#-------------------------------------------------

QT       += core
QT       += xml
QT       -= gui

TARGET = TimeRecord4th
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    recordautosort.cpp \
    recordname.cpp \
    smsreader.cpp \
    GTDxml.cpp \
    stlrecord.cpp \
    namewithsortnumreturnrecord.cpp \
    recordgetandpost.cpp \
    todolist.cpp

HEADERS += \
    globe.h \
    recordautosort.h \
    recordname.h \
    smsreader.h \
    GTDxml.h \
    stlrecord.h \
    namewithsortnumreturnrecord.h \
    recordgetandpost.h \
    todolist.h
