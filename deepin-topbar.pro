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
service.files = com.deepin.dde.topbar.service

desktop.path = $${PREFIX}/share/applications/
desktop.files = deepin-topbar.desktop

icon.path = $$PREFIX/share/icons/hicolor/scalable/apps
icon.files = deepin-topbar.svg

polkit.path = $${PREFIX}/share/polkit-1/actions
polkit.files = com.deepin.dde.topbar.polkit.service

INSTALLS += desktop service qm_files icon
