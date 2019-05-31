cmake_minimum_required(VERSION 3.7)

set(VERSION 4.0)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(BIN_NAME "deepin-topbar")

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

set(FRAME_FILES
./frame/dbusservice.cpp
./frame/dbusservice.h
./frame/item/contentmodule.cpp
./frame/item/contentmodule.h
./frame/item/stretchitem.cpp
./frame/item/stretchitem.h
./frame/item/item.cpp
./frame/item/item.h
./frame/item/pluginsitem.cpp
./frame/item/pluginsitem.h
# ./frame/maindbusservice.cpp
# ./frame/maindbusservice.h
./frame/settings.cpp
./frame/settings.h
# ./frame/utils/event_monitor.cpp
# ./frame/utils/event_monitor.h
./frame/utils/global.cpp
./frame/utils/global.h
./frame/utils/themeappicon.cpp
./frame/utils/themeappicon.h
./frame/main.cpp
./frame/mainframe.cpp
./frame/mainframe.h
./frame/mainpanel.h
./frame/mainpanel.cpp
)

set(DBUS_FILES
./dbus/com_deepin_dde_wallpaper.cpp
./dbus/com_deepin_dde_wallpaper.h
./dbus/dbusaccount.cpp
./dbus/dbusaccount.h
./dbus/dbusaudio.cpp
./dbus/dbusaudio.h
./dbus/dbusinterface.cpp
./dbus/dbusinterface.h
./dbus/dbusmediaplayer2.cpp
./dbus/dbusmediaplayer2.h
./dbus/dbussink.cpp
./dbus/dbussink.h
./dbus/dbussinkinput.cpp
./dbus/dbussinkinput.h
)

set(WIDGETS_FILES
./widgets/dactionbutton.h
./widgets/dactionlabel.cpp
./widgets/dactionlabel.h
./widgets/dwidgetaction.cpp
./widgets/dwidgetaction.h
./widgets/fontlabel.h
./widgets/switchbutton.cpp
./widgets/switchbutton.h
./widgets/dactionbutton.cpp
./widgets/fontlabel.cpp
./widgets/itempopupwindow.cpp
./widgets/itempopupwindow.h
./widgets/switchitem.cpp
./widgets/switchitem.h
)

set(INTERFACES_FILES
./interfaces/moduleiteminterface.h
./interfaces/pluginproxyinterface.h
./interfaces/pluginsiteminterface.h
)

set(ACCOUNT_FILES
./modules/account/accountplugin.cpp
./modules/account/accountplugin.h
./modules/account/accountwidget.cpp
./modules/account/accountwidget.h
)

set(INDICATOR_FILES
./modules/indicator/View/appstoreaction.cpp
./modules/indicator/View/appstoreaction.h
./modules/indicator/View/entry.cpp
./modules/indicator/View/entry.h
./modules/indicator/View/positionwidget.cpp
./modules/indicator/View/positionwidget.h
./modules/indicator/View/indicatorwidget.cpp
./modules/indicator/View/indicatorwidget.h
./modules/indicator/View/systemlogo.cpp
./modules/indicator/View/systemlogo.h
./modules/indicator/indicatormodel.cpp
./modules/indicator/indicatormodel.h
./modules/indicator/indicatorworker.cpp
./modules/indicator/indicatorworker.h
./modules/indicator/indicatorplugin.cpp
./modules/indicator/indicatorplugin.h
)

set(NETWORK_FILES
./modules/network/item/applet/refreshaction.cpp
./modules/network/item/applet/refreshaction.h
./modules/network/item/applet/accesspoint.cpp
./modules/network/item/applet/accesspoint.h
./modules/network/networkcontrolpanel.cpp
./modules/network/networkcontrolpanel.h
./modules/network/networkdelegate.cpp
./modules/network/networkdelegate.h
./modules/network/networklistmodel.cpp
./modules/network/networklistmodel.h
./modules/network/networklistview.cpp
./modules/network/networklistview.h
./modules/network/networkplugin.cpp
./modules/network/networkplugin.h
)

set(NOTIFY_FILES
./modules/notify/notifyplugin.h
./modules/notify/notifyplugin.cpp
./modules/notify/notifydelegate.cpp
./modules/notify/notifydelegate.h
./modules/notify/notifymodel.cpp
./modules/notify/notifymodel.h
./modules/notify/notifyview.cpp
./modules/notify/notifyview.h
./modules/notify/notifywidget.cpp
./modules/notify/notifywidget.h
)

set(POWER_FILES
./modules/power/powerwidgetaction.h
./modules/power/powerplugin.cpp
./modules/power/powerplugin.h
./modules/power/powerwidget.cpp
./modules/power/powerwidget.h
./modules/power/powerwidgetaction.cpp
)

set(SEARCH_FILES
./modules/search/searchbutton.cpp
./modules/search/searchbutton.h
./modules/search/searchmodule.cpp
./modules/search/searchmodule.h
)

set(SOUND_FILES
./modules/sound/componments/horizontalseparator.cpp
./modules/sound/componments/horizontalseparator.h
./modules/sound/componments/mediacontrol.cpp
./modules/sound/componments/mediacontrol.h
./modules/sound/componments/volumeslider.cpp
./modules/sound/componments/volumeslider.h
./modules/sound/sinkinputwidget.cpp
./modules/sound/sinkinputwidget.h
./modules/sound/soundapplet.cpp
./modules/sound/soundapplet.h
./modules/sound/sounditem.cpp
./modules/sound/sounditem.h
./modules/sound/soundplugin.cpp
./modules/sound/soundplugin.h
)

set(SYSTEM_TRAY_FILES
./modules/system-tray/abstracttraywidget.cpp
./modules/system-tray/abstracttraywidget.h
./modules/system-tray/dbus/dbustraymanager.cpp
./modules/system-tray/dbus/dbustraymanager.h
./modules/system-tray/dbus/sni/dbusstructures.cpp
./modules/system-tray/dbus/sni/dbusstructures.h
./modules/system-tray/dbus/sni/statusnotifieritem_interface.cpp
./modules/system-tray/dbus/sni/statusnotifieritem_interface.h
./modules/system-tray/dbus/sni/statusnotifierwatcheradapter.cpp
./modules/system-tray/dbus/sni/statusnotifierwatcheradapter.h
./modules/system-tray/traypanel.cpp
./modules/system-tray/traypanel.h
./modules/system-tray/xwindowtraywidget.cpp
./modules/system-tray/xwindowtraywidget.h
./modules/system-tray/sni/statusnotifierwatcher.cpp
./modules/system-tray/sni/statusnotifierwatcher.h
./modules/system-tray/snitraywidget.cpp
./modules/system-tray/snitraywidget.h
./modules/system-tray/systemtrayplugin.cpp
./modules/system-tray/systemtrayplugin.h
./modules/system-tray/tipswidget.cpp
./modules/system-tray/tipswidget.h
)

set(SYSTEM_INFO_FILES
./modules/systeminfo/DBus/org_freedesktop_networkmanager.cpp
./modules/systeminfo/DBus/org_freedesktop_networkmanager.h
./modules/systeminfo/DBus/org_freedesktop_networkmanager_activeconnection.cpp
./modules/systeminfo/DBus/org_freedesktop_networkmanager_activeconnection.h
./modules/systeminfo/DBus/org_freedesktop_networkmanager_device.cpp
./modules/systeminfo/DBus/org_freedesktop_networkmanager_device.h
./modules/systeminfo/systeminfomodel.cpp
./modules/systeminfo/systeminfomodel.h
./modules/systeminfo/systeminfoplugin.cpp
./modules/systeminfo/systeminfoplugin.h
./modules/systeminfo/systeminfopopupwidget.cpp
./modules/systeminfo/systeminfopopupwidget.h
./modules/systeminfo/systeminfothread.cpp
./modules/systeminfo/systeminfothread.h
./modules/systeminfo/systeminfowidget.cpp
./modules/systeminfo/systeminfowidget.h
)

set(DATETIME_FILES
./modules/timewidget/datetimewidget.cpp
./modules/timewidget/datetimewidget.h
./modules/timewidget/datetimeplugin.cpp
./modules/timewidget/datetimeplugin.h
)

set(ALL_FILES
    ${FRAME_FILES}
    ${DBUS_FILES}
    ${WIDGETS_FILES}
    ${INTERFACES_FILES}
    ${ACCOUNT_FILES}
    ${INDICATOR_FILES}
    ${NETWORK_FILES}
    ${NOTIFY_FILES}
    ${POWER_FILES}
    ${SEARCH_FILES}
    ${SOUND_FILES}
    ${SYSTEM_TRAY_FILES}
    ${SYSTEM_INFO_FILES}
    ${DATETIME_FILES}
)

set(QRC_FILES
./frame/deepin-topbar.qrc
./widgets/widgets.qrc
./modules/indicator/indicator.qrc
./modules/network/network.qrc
./modules/power/power.qrc
./modules/sound/resources/sound.qrc
./modules/system-tray/system-tray.qrc
./modules/systeminfo/resources/systeminfo.qrc
./modules/notify/notify.qrc
)

if(DEFINED ENABLE_RATOTE)
    add_definitions(-DENABLE_RATOTE)
endif()

# Find the library
find_package(PkgConfig REQUIRED)
find_package(DtkWidget REQUIRED)
find_package(Qt5 COMPONENTS Core Gui DBus Svg X11Extras Concurrent REQUIRED)

pkg_check_modules(PROCPS REQUIRED libprocps)
pkg_check_modules(XCB_LIBS REQUIRED xcb-ewmh xcb xcb-image xcb-composite xtst xcb-icccm dbusmenu-qt5)
pkg_check_modules(XCB_EWMH REQUIRED xcb-ewmh x11 xext)
pkg_check_modules(DFrameworkDBus REQUIRED dframeworkdbus)
pkg_check_modules(DDE-Network-Utils REQUIRED dde-network-utils)
pkg_check_modules(QGSettings REQUIRED gsettings-qt)

add_executable(${BIN_NAME} ${ALL_FILES} ${QRC_FILES})
target_include_directories(${BIN_NAME} PUBLIC
                                        ${DtkWidget_INCLUDE_DIRS}
                                        ${XCB_EWMH_INCLUDE_DIRS}
                                        ${DFrameworkDBus_INCLUDE_DIRS}
                                        ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
                                        ${Qt5DBus_INCLUDE_DIRS}
                                        ${QGSettings_INCLUDE_DIRS}
                                        ${DDE-Network-Utils_INCLUDE_DIRS}
                                        ${XCB_LIBS_INCLUDE_DIRS}
                                        ${PROJECT_BINARY_DIR}
)

target_link_libraries(${BIN_NAME} PRIVATE
        ${DFrameworkDBus_LIBRARIES}
        ${QGSettings_LIBRARIES}
        ${DDE-Network-Utils_LIBRARIES}
        ${XCB_LIBS_LIBRARIES}
        ${XCB_EWMH_LIBRARIES}
        ${DtkWidget_LIBRARIES}
        Qt5::Core
        Qt5::Gui
        Qt5::Svg
        Qt5::DBus
        Qt5::X11Extras
        Qt5::Concurrent
        ${PROCPS_LIBRARIES}
)

# bin
install(TARGETS ${BIN_NAME} DESTINATION bin)
