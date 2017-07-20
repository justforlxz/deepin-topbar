#-------------------------------------------------
#
# Project created by QtCreator 2017-06-19T19:00:44
#
#-------------------------------------------------


include(../../interfaces/interfaces.pri)
include(../../widgets/widgets.pri)

QT       += core gui widgets dbus x11extras
PKGCONFIG += dtkwidget dtkbase dtkutil dframeworkdbus
TEMPLATE = lib
CONFIG    += plugin c++11 link_pkgconfig
TARGET     = $$qtLibraryTarget(power)
DESTDIR    = $$_PRO_FILE_PWD_/../
DISTFILES += power.json \
    DBus/com.deepin.daemon.Power.xml
DEFINES += POWER_LIBRARY

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
        powerplugin.cpp \
    powerwidget.cpp \
    powerpopupwidget.cpp \
    DBus/dbusaccount.cpp \
    DBus/dbuspower.cpp

HEADERS += \
        powerplugin.h \
    powerwidget.h \
    powerpopupwidget.h \
    DBus/dbusaccount.h \
    DBus/dbuspower.h

target.path = $${PREFIX}/lib/deepin-topbar/plugins/
INSTALLS   += target

RESOURCES += \
    power.qrc
