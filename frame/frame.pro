include(../interfaces/interfaces.pri)
include(../widgets/widgets.pri)

QT       += core gui x11extras widgets dbus

TARGET = deepin-topbar
TEMPLATE = app
CONFIG         += c++11 link_pkgconfig
DESTDIR         = $$_PRO_FILE_PWD_/../
PKGCONFIG += xcb-ewmh dtkcore dtkwidget dframeworkdbus x11 xcb-util xtst xext

HEADERS  += \
    mainframe.h \
    controller/pluginloader.h \
    controller/pluginscontroller.h \
    item/pluginsitem.h \
    controller/pluginsitemcontroller.h \
    mainpanel.h \
    item/item.h \
    item/stretchitem.h \
    utils/itempopupwindow.h \
    utils/event_monitor.h \
    dbus/dbusmenu.h \
    dbus/dbusmenumanager.h

SOURCES += \
    main.cpp\
    mainframe.cpp \
    controller/pluginloader.cpp \
    controller/pluginscontroller.cpp \
    item/pluginsitem.cpp \
    controller/pluginsitemcontroller.cpp \
    mainpanel.cpp \
    item/item.cpp \
    item/stretchitem.cpp \
    utils/itempopupwindow.cpp \
    utils/event_monitor.cpp \
    dbus/dbusmenu.cpp \
    dbus/dbusmenumanager.cpp

headers.files += ../interfaces/pluginsiteminterface.h \
                 ../interfaces/pluginproxyinterface.h
headers.path = $${PREFIX}/include/deepin-topbar

target.path = $${PREFIX}/bin/
INSTALLS += target headers
