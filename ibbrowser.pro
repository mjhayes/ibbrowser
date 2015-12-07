#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T20:52:59
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ibbrowser
TEMPLATE = app


SOURCES += main.cpp \
    commandserver.cpp \
    commandclient.cpp \
    ittywebview.cpp \
    mydaemon.cpp

HEADERS  += \
    commandserver.h \
    commandclient.h \
    ittywebview.h \
    mydaemon.h

FORMS    +=
