TEMPLATE = subdirs
SUBDIRS = frame \
          plugins

isEmpty(PREFIX) {
    PREFIX = /usr
}

service.path = $${PREFIX}/share/dbus-1/services
service.files = com.deepin.deepin.Topbar.service

desktop.path = $${PREFIX}/share/applications/
desktop.files = deepin-topbar.desktop

autostart.path = /etc/xdg/autostart/
autostart.files = deepin-topbar-autostart.desktop

INSTALLS += desktop service autostart
