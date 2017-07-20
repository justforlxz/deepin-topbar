#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T23:56:20
#
#-------------------------------------------------

include(../../interfaces/interfaces.pri)

QT       += core gui widgets x11extras dbus concurrent
PKGCONFIG += dtkwidget dtkbase dtkutil dframeworkdbus
TEMPLATE = lib
CONFIG    += plugin c++11 link_pkgconfig
TARGET     = $$qtLibraryTarget(indicator)
DESTDIR    = $$_PRO_FILE_PWD_/../
DISTFILES += indicator.json

DEFINES += INDICATOR_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        indicatorplugin.cpp \
    View/indicatorwidget.cpp \
    DBus/dbusdock.cpp \
    DBus/dbusdockentry.cpp \
    View/entry.cpp \
    themeappicon.cpp

HEADERS += \
        indicatorplugin.h \
    View/indicatorwidget.h \
    DBus/dbusdock.h \
    DBus/dbusdockentry.h \
    View/entry.h \
    themeappicon.h

target.path = $${PREFIX}/lib/deepin-topbar/plugins/
INSTALLS   += target

RESOURCES +=
