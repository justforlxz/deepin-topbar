HEADERS += \
    $$PWD/systemtrayplugin.h \
    $$PWD/dbus/dbustraymanager.h \
    $$PWD/tipswidget.h \
    $$PWD/xwindowtraywidget.h \
    $$PWD/abstracttraywidget.h \
    $$PWD/sni/statusnotifierwatcher.h \
    $$PWD/dbus/sni/statusnotifierwatcheradapter.h \
    $$PWD/dbus/sni/dbusstructures.h \
    $$PWD/dbus/sni/statusnotifieritem_interface.h \
    $$PWD/snitraywidget.h

SOURCES += \
    $$PWD/systemtrayplugin.cpp \
    $$PWD/dbus/dbustraymanager.cpp \
    $$PWD/tipswidget.cpp \
    $$PWD/xwindowtraywidget.cpp \
    $$PWD/abstracttraywidget.cpp \
    $$PWD/sni/statusnotifierwatcher.cpp \
    $$PWD/dbus/sni/statusnotifierwatcheradapter.cpp \
    $$PWD/dbus/sni/dbusstructures.cpp \
    $$PWD/dbus/sni/statusnotifieritem_interface.cpp \
    $$PWD/snitraywidget.cpp

RESOURCES += \
    $$PWD/system-tray.qrc
