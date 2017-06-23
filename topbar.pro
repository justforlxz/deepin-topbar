TEMPLATE = subdirs
SUBDIRS = frame \
          plugins

isEmpty(PREFIX) {
    PREFIX = /usr
}

service.path = $${PREFIX}/share/dbus-1/services
service.files = com.deepin.dde.Topbar.service

desktop.path = $${PREFIX}/share/applications/
desktop.files = dde-topbar.desktop

INSTALLS += desktop service
