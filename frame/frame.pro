include(../interfaces/interfaces.pri)
include(../widgets/widgets.pri)
include(../modules/modules.pri)
include(../dbus/dbus.pri)

QT       += core gui x11extras widgets dbus concurrent svg

TARGET = deepin-topbar
TEMPLATE = app
CONFIG         += c++11 link_pkgconfig
DESTDIR         = $$_PRO_FILE_PWD_/../
PKGCONFIG += xcb-ewmh dtkcore dtkwidget \
             dframeworkdbus x11 xcb-util \
             xtst xext gsettings-qt xcb-image \
             xcb-icccm xcb-composite gsettings-qt

HEADERS  += \
    $$PWD/mainframe.h \
    $$PWD/item/pluginsitem.h \
    $$PWD/mainpanel.h \
    $$PWD/item/item.h \
    $$PWD/item/stretchitem.h \
    $$PWD/utils/itempopupwindow.h \
    $$PWD/utils/event_monitor.h \
    item/contentmodule.h \
    utils/global.h

SOURCES += \
    $$PWD/main.cpp\
    $$PWD/mainframe.cpp \
    $$PWD/item/pluginsitem.cpp \
    $$PWD/mainpanel.cpp \
    $$PWD/item/item.cpp \
    $$PWD/item/stretchitem.cpp \
    $$PWD/utils/itempopupwindow.cpp \
    $$PWD/utils/event_monitor.cpp \
    item/contentmodule.cpp \
    utils/global.cpp

headers.files += ../interfaces/pluginsiteminterface.h \
                 ../interfaces/pluginproxyinterface.h
headers.path = $${PREFIX}/include/deepin-topbar

target.path = $${PREFIX}/bin/
INSTALLS += target headers
