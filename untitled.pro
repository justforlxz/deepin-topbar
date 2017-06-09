#-------------------------------------------------
#
# Project created by QtCreator 2017-06-09T10:16:49
#
#-------------------------------------------------

QT       += core gui x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

CONFIG         += c++11 link_pkgconfig

PKGCONFIG += xcb-ewmh dtkwidget dtkbase dtkutil x11


SOURCES += main.cpp\
        Widget.cpp \
    XcbMisc.cpp \
    topbar.cpp \
    timewidget.cpp

HEADERS  += Widget.h \
    XcbMisc.h \
    topbar.h \
    timewidget.h
