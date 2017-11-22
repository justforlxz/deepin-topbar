TEMPLATE = subdirs
SUBDIRS = frame

isEmpty(PREFIX) {
    PREFIX = /usr
}

# Automating generation .qm files from .ts files
!system($$PWD/translate_generation.sh): error("Failed to generate translation")

qm_files.path = $${PREFIX}/share/deepin-topbar/translations/
qm_files.files = translations/*.qm

service.path = $${PREFIX}/share/dbus-1/services
service.files = com.deepin.deepin.Topbar.service

desktop.path = $${PREFIX}/share/applications/
desktop.files = deepin-topbar.desktop

autostart.path = /etc/xdg/autostart/
autostart.files = deepin-topbar-autostart.desktop

icon.path = $${PREFIX}/share/deepin-topbar/icons
icon.files = deepin-topbar.svg

INSTALLS += desktop service autostart qm_files icon
