#-------------------------------------------------
#
# Project created by QtCreator 2017-06-09T14:02:47
#
#-------------------------------------------------

include(../../interfaces/interfaces.pri)

QT        += core gui widgets
PKGCONFIG += dtkwidget dtkbase dtkutil
TEMPLATE   = lib
CONFIG    += c++11 link_pkgconfig
TARGET     = $$qtLibraryTarget(datetime)
DESTDIR    = $$_PRO_FILE_PWD_/../
DISTFILES += datetime.json

SOURCES   += \
    datetimewidget.cpp \
    datetimeplugin.cpp \
    datetimepopup.cpp \
    switchitem.cpp

HEADERS   += \
    datetimewidget.h \
    datetimeplugin.h \
    datetimepopup.h \
    switchitem.h

target.path = $${PREFIX}/lib/dde-topbar/plugins/
INSTALLS   += target
