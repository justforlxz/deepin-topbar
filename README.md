# Deepin Topbar

This is a project that I have a whim to help improve my ability to write code.

## Dependencies

### Build dependencies

* qmake (>= 5.3)
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

If you use Deepin, just add my ppa. see [here](https://blog.mkacg.com/2017/07/20/topbar-PPA/)

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

The executable binary file could be found at `/usr/bin/deepin-topbar` after the installation is finished, and plugins will be placed into `/usr/lib/deepin-topbar/plugins/`.

## Getting help

You can create a issue, I will help you.

You may also find these channels useful if you encounter any other issues:

* [deepin community](https://bbs.deepin.org) Topbar is also the community software that you can post for help.

## License

Deepin-topbar is licensed under [GPLv3](LICENSE).

## Want to know how to help me?

It's simple.

* fork and pull request. I want more people to help me improve it.

* Help me with money. It's no joke. I need money to pay for some service, and I'll make public any contribution.

# alipay (支付宝)
![alipay](readme/zhifubao.jpg) 

# wechat (微信)
![wechat](readme/weixin.jpg)

# paypal
[Paypal](paypal.me/zhangdingyuan)