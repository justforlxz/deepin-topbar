include(../interfaces/interfaces.pri)

QT       += core gui x11extras widgets dbus

TARGET = dde-topbar
TEMPLATE = app
CONFIG         += c++11 link_pkgconfig

PKGCONFIG += xcb-ewmh dtkwidget dtkbase dtkutil x11

HEADERS  += \
    xcb-misc/XcbMisc.h \
    topbar.h \
    mainframe.h \
    controller/pluginloader.h \
    controller/pluginscontroller.h \
    item/pluginsitem.h \
    dbus/dbusmenumanager.h \
    dbus/dbusmenu.h

SOURCES += \
    main.cpp\
    xcb-misc/XcbMisc.cpp \
    topbar.cpp \
    mainframe.cpp \
    controller/pluginloader.cpp \
    controller/pluginscontroller.cpp \
    item/pluginsitem.cpp \
    dbus/dbusmenumanager.cpp \
    dbus/dbusmenu.cpp

target.path = $${PREFIX}/bin/
INSTALL += target
