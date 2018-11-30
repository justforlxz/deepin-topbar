DEFINES += QT_MESSAGELOGCONTEXT

INCLUDEPATH += $$PWD

isEmpty(PREFIX)
{
    PREFIX = /usr
}

DISTFILES += \
    $$PWD/dbus.pri \
    $$PWD/com.deepin.daemon.Audio.Sink.xml \
    $$PWD/com.deepin.daemon.Audio.SinkInput.xml \
    $$PWD/com.deepin.daemon.Audio.xml \
    $$PWD/com.deepin.daemon.Power.xml \
    $$PWD/com.deepin.dde.Wallpaper.xml \
    $$PWD/org.mpris.MediaPlayer2.xml

HEADERS += \
    $$PWD/com_deepin_dde_wallpaper.h \
    $$PWD/dbusaccount.h \
    $$PWD/dbusaudio.h \
    $$PWD/dbusdockentry.h \
    $$PWD/dbusinterface.h \
    $$PWD/dbusmediaplayer2.h \
    $$PWD/dbusnetwork.h \
    $$PWD/dbuspower.h \
    $$PWD/dbussink.h \
    $$PWD/dbussinkinput.h

SOURCES += \
    $$PWD/com_deepin_dde_wallpaper.cpp \
    $$PWD/dbusaccount.cpp \
    $$PWD/dbusaudio.cpp \
    $$PWD/dbusdockentry.cpp \
    $$PWD/dbusinterface.cpp \
    $$PWD/dbusmediaplayer2.cpp \
    $$PWD/dbusnetwork.cpp \
    $$PWD/dbuspower.cpp \
    $$PWD/dbussink.cpp \
    $$PWD/dbussinkinput.cpp
