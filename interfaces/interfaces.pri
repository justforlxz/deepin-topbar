DEFINES += QT_MESSAGELOGCONTEXT

HEADERS += \
    $$PWD/pluginsiteminterface.h \
    $$PWD/pluginproxyinterface.h \
    $$PWD/constants.h

SOURCES += \

INCLUDEPATH += $$PWD

isEmpty(PREFIX)
{
    PREFIX = /usr
}
