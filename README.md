# Deepin Topbar

This is a project that I have a whim to help improve my ability to write code.

## How to get my message and software updates?

I'll release messages on my twitter and google plus.

[Twitter @haruyukilxz](https://twitter.com/haruyukilxz)

[Google+](https://plus.google.com/+kirigayakazushin)

## Dependencies

### Build dependencies

* Qt5 (>= 5.6)
* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit) (developer package)
* [dde-qt-dbus-factory](https://github.com/linuxdeepin/dde-qt-dbus-factory)
(developer package)
* [deepin-qt5integration](https://github.com/linuxdeepin/deepin-qt5integration)
(developer package)
* xcb-ewmh (developer package)
* xcb-util (developer package)
* xtst (developer package)
* xcb-image (developer package)
* xcb-icccm (developer package)
* xcb-composite (developer package)

### Runtime dependencies

* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit)
* [dde-api](https://github.com/linuxdeepin/dde-api)
* [dde-daemon](https://github.com/linuxdeepin/dde-daemon)
* [dde-qt-dbus-factory](https://github.com/linuxdeepin/dde-qt-dbus-factory)
* [deepin-qt5integration](https://github.com/linuxdeepin/deepin-qt5integration)
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

<p align="center"><img src="https://user-images.githubusercontent.com/12298476/40405507-6f0b97c0-5e8f-11e8-913c-f093b3f5005f.png"></p>
<p align="center"><img src="https://user-images.githubusercontent.com/12298476/40405509-6f5d3288-5e8f-11e8-95f2-4acd2f6545eb.gif"></p>

If you use Deepin, just add my ppa. see [here](https://blog.ilxz.me/topbar-ppa/)

If you use Arch, you can install deepin-topbar with aur.

## Installation

### Build from source code

1. Make sure you have installed all dependencies.

2. Build:
```
$ cd deepin-topbar
$ mkdir Build
$ cd Build
$ qmake ..
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