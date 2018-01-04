#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T02:00:03
#
#-------------------------------------------------

QT       += core gui

QT += network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hangman
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    serwer.cpp \
    klient.cpp

HEADERS  += widget.h \
    serwer.h \
    klient.h

FORMS    += widget.ui
