plugin dependency:

```
power: linux-cpupower
```

Compile dependency:
```
sudo apt install libdtkwidget-dev libdtkutil-dev libdtkbase-dev libxcb-ewmh-dev libdframeworkdbus-dev qt5-default g++
```

build and install

```
git clone https://github.com/kirigayakazushin/deepin-topbar.git
```

```
cd deepin-topbar && mkdir build && cd build
```

```
qmake ../
```

```
make
```

```
sudo make install
```

find topbar on launcher, and run it.
