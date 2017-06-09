#-------------------------------------------------
#
# Project created by QtCreator 2017-06-09T14:02:47
#
#-------------------------------------------------

include(../../interfaces/interfaces.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeWIdget
TEMPLATE = lib
CONFIG         += c++11 link_pkgconfig

SOURCES += \
    datetimewidget.cpp \
    datetimeplugin.cpp

HEADERS  += \
    datetimewidget.h \
    datetimeplugin.h

target.path = $${PREFIX}/lib/dde-topbar/plugins/
INSTALLS += target
