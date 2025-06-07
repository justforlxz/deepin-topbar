# Deepin Topbar

This is a project that I have a whim to help improve my ability to write code.

## How to get my message and software updates?

I'll release messages on my twitter.

[Twitter @justforlxz](https://twitter.com/justforlxz)

## ToDo List
- [ ] Network (wireless list)
- [ ] Calendar (Only see web ical, no plans to support editting)
- [ ] Global Menu (Non-primary)
- [ ] quick search (maybe will create new repo)
- [ ] system info (e.g. cpu, memory, disk historical graph)
- [ ] power save (use dde function)

## Finished
- [x] Current Window Indicator
- [x] Position
- [x] Network Speed
- [x] system tray
- [x] Sound and media control
- [x] power and battery
- [x] datetime
- [x] Notify list

## Dependencies

### Build dependencies

* Qt5 (>= 5.6)
* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit) (developer package)
* [dde-qt-dbus-factory](https://github.com/linuxdeepin/dde-qt-dbus-factory) (developer package)
* [deepin-qt5integration](https://github.com/linuxdeepin/deepin-qt5integration) (developer package)
* [dde-network-utils](https://github.com/linuxdeepin/libdde-network-utils-dev) (developer package)
* xcb-ewmh (developer package)
* xcb-util (developer package)
* xtst (developer package)
* xcb-image (developer package)
* xcb-icccm (developer package)
* xcb-composite (developer package)
* procps (developer package)
* cmake (build package)

### Runtime dependencies

* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit)
* [dde-api](https://github.com/linuxdeepin/dde-api)
* [dde-daemon](https://github.com/linuxdeepin/dde-daemon)
* [dde-qt-dbus-factory](https://github.com/linuxdeepin/dde-qt-dbus-factory)
* [deepin-qt5integration](https://github.com/linuxdeepin/deepin-qt5integration)
* [dde-network-utils](https://github.com/linuxdeepin/libdde-network-utils-dev)
* linux-cpupower
* Qt5 (>= 5.6)
  * Qt5-DBus
  * Qt5-Multimedia
  * Qt5-MultimediaWidgets
  * Qt5-Svg
  * Qt5-X11extras
* xcb-ewmh
* xcb-util
* xtst
* xcb-image
* xcb-icccm
* xcb-composite

## Partial Preview

<p align="center"><img src="https://user-images.githubusercontent.com/12298476/49862366-04af7a00-fe39-11e8-9d46-3c33515db270.gif"></p>
<p align="center"><img src="https://user-images.githubusercontent.com/12298476/49862451-29a3ed00-fe39-11e8-9a4a-6118ef27564d.png"></p>

If you use Deepin, just install from appstore.

If you use Arch, you can install deepin-topbar in Community repo.

## Installation

### Build from source code

1. Make sure you have installed all dependencies.

2. Build:
```
$ cd deepin-topbar
$ mkdir Build
$ cd Build
$ cmake ../
$ make
```

3. Install:
```
$ sudo make install
```

The executable binary file could be found at `/usr/bin/deepin-topbar` after the installation is finished.

## Getting help

You can create a issue, I will help you.

You may also find these channels useful if you encounter any other issues:

* [deepin community](https://bbs.deepin.org) Topbar is also the community software that you can post for help.

## License

Deepin-topbar is licensed under [GPLv3](LICENSE).

## Want to know how to help me?

It's simple.

* fork and pull request. I want more people to help me improve it.

[![Powered by DartNode](https://dartnode.com/branding/DN-Open-Source-sm.png)](https://dartnode.com "Powered by DartNode - Free VPS for Open Source")
