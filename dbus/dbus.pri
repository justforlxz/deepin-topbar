DEFINES += QT_MESSAGELOGCONTEXT

INCLUDEPATH += $$PWD

isEmpty(PREFIX)
{
    PREFIX = /usr
}

HEADERS += \
    $$PWD/dbusaccount.h \
    $$PWD/dbusaudio.h \
    $$PWD/dbusdock.h \
    $$PWD/dbusdockentry.h \
    $$PWD/dbusinterface.h \
    $$PWD/dbusmediaplayer2.h \
    $$PWD/dbusnetwork.h \
    $$PWD/dbuspower.h \
    $$PWD/dbussink.h \
    $$PWD/dbussinkinput.h

SOURCES += \
    $$PWD/dbusaccount.cpp \
    $$PWD/dbusaudio.cpp \
    $$PWD/dbusdock.cpp \
    $$PWD/dbusdockentry.cpp \
    $$PWD/dbusinterface.cpp \
    $$PWD/dbusmediaplayer2.cpp \
    $$PWD/dbusnetwork.cpp \
    $$PWD/dbuspower.cpp \
    $$PWD/dbussink.cpp \
    $$PWD/dbussinkinput.cpp
