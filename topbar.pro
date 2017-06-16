TEMPLATE = subdirs
SUBDIRS = frame \
          plugins

isEmpty(PREFIX) {
    PREFIX = /usr
}

service.path = $${PREFIX}/share/dbus-1/services
service.files = com.deepin.dde.Topbar.service

binary.path = $${PREFIX}/bin
binary.files = dde-topbar

desktop.path = $${PREFIX}/share/applications/
desktop.files = dde-topbar.desktop

INSTALLS += binary desktop service
