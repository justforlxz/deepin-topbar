include(../interfaces/interfaces.pri)
include(../widgets/widgets.pri)
include(../modules/modules.pri)
include(../dbus/dbus.pri)

QT       += core gui x11extras widgets dbus concurrent svg

TARGET = deepin-topbar
TEMPLATE = app
CONFIG         += c++11 link_pkgconfig
DESTDIR         = $$_PRO_FILE_PWD_/../
PKGCONFIG += xcb-ewmh \
             dtkcore \
             dtkwidget \
             dframeworkdbus \
             gsettings-qt \
             x11 \
             xcb-util \
             xtst \
             xext \
             xcb-image \
             xcb-icccm \
             xcb-composite

HEADERS  += \
    mainframe.h \
    item/pluginsitem.h \
    mainpanel.h \
    item/item.h \
    item/stretchitem.h \
    utils/itempopupwindow.h \
    utils/event_monitor.h \
    item/contentmodule.h \
    utils/global.h \
    settings.h \
    dbusservice.h

SOURCES += \
    main.cpp\
    mainframe.cpp \
    item/pluginsitem.cpp \
    mainpanel.cpp \
    item/item.cpp \
    item/stretchitem.cpp \
    utils/itempopupwindow.cpp \
    utils/event_monitor.cpp \
    item/contentmodule.cpp \
    utils/global.cpp \
    settings.cpp \
    dbusservice.cpp

headers.files += ../interfaces/pluginsiteminterface.h \
                 ../interfaces/pluginproxyinterface.h
headers.path = $${PREFIX}/include/deepin-topbar

target.path = $${PREFIX}/bin/
INSTALLS += target headers

RESOURCES += \
    deepin-topbar.qrc
