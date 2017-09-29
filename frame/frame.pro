include(../interfaces/interfaces.pri)
include(../widgets/widgets.pri)
include(../modules/modules.pri)
include(../dbus/dbus.pri)

QT       += core gui x11extras widgets dbus concurrent

TARGET = deepin-topbar
TEMPLATE = app
CONFIG         += c++11 link_pkgconfig
DESTDIR         = $$_PRO_FILE_PWD_/../
PKGCONFIG += xcb-ewmh dtkcore dtkwidget \
             dframeworkdbus x11 xcb-util \
             xtst xext gsettings-qt

HEADERS  += \
    $$PWD/mainframe.h \
    $$PWD/controller/pluginloader.h \
    $$PWD/controller/pluginscontroller.h \
    $$PWD/item/pluginsitem.h \
    $$PWD/controller/pluginsitemcontroller.h \
    $$PWD/mainpanel.h \
    $$PWD/item/item.h \
    $$PWD/item/stretchitem.h \
    $$PWD/utils/itempopupwindow.h \
    $$PWD/utils/event_monitor.h \
    $$PWD/dbus/dbusmenu.h \
    $$PWD/dbus/dbusmenumanager.h

SOURCES += \
    $$PWD/main.cpp\
    $$PWD/mainframe.cpp \
    $$PWD/controller/pluginloader.cpp \
    $$PWD/controller/pluginscontroller.cpp \
    $$PWD/item/pluginsitem.cpp \
    $$PWD/controller/pluginsitemcontroller.cpp \
    $$PWD/mainpanel.cpp \
    $$PWD/item/item.cpp \
    $$PWD/item/stretchitem.cpp \
    $$PWD/utils/itempopupwindow.cpp \
    $$PWD/utils/event_monitor.cpp \
    $$PWD/dbus/dbusmenu.cpp \
    $$PWD/dbus/dbusmenumanager.cpp

headers.files += ../interfaces/pluginsiteminterface.h \
                 ../interfaces/pluginproxyinterface.h
headers.path = $${PREFIX}/include/deepin-topbar

target.path = $${PREFIX}/bin/
INSTALLS += target headers
