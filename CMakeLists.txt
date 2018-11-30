cmake_minimum_required(VERSION 3.7)

project(deepin-topbar)

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

add_subdirectory(src)

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

    # generate qm
    execute_process(COMMAND bash "translate_generation.sh"
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif ()

## qm files
file(GLOB QM_FILES "translations/*.qm")
install(FILES ${QM_FILES}
        DESTINATION share/deepin-topbar/translations)

## services files
install(FILES com.deepin.dde.topbar.service
DESTINATION share/dbus-1/services)

## polkit
install(FILES com.deepin.dde.topbar.polkit.service
DESTINATION share/polkit-1/actions)

## icon
install(FILES deepin-topbar.svg deepin-logo.svg
DESTINATION share/icons/hicolor/scalable/apps)

# desktop
install(FILES deepin-topbar.desktop
DESTINATION share/applications/)
