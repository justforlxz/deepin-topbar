# install script by zimo
# 1.install all dependencies and tools.
sudo install qt5* -y
sudo apt install qttools5-dev -y
sudo apt install libgsettings-qt-dev -y
sudo apt install libdde-network-ut* -y
sudo apt install libdframeworkdbus* -y
sudo apt install libdbusmenu-qt5-dev -y
sudo apt install libxcb-ewmh-dev -y
sudo apt install libxcb-util* -y
sudo apt install libxtst* -y
sudo apt install libxcb-im* -y
sudo apt install libxcb-ic* -y
sudo apt install libxcb-co* -y
sudo apt install dde-dock-dev -y
sudo apt install qtbase5-dev-tools -y
sudo apt install libdtkwidget-dev -y
sudo apt install libxcb-composite0-dev -y
sudo apt install libprocps-dev -y
sudo apt install cmake -y

# 2. build
mkdir Build
cd Build
cmake ../
make

# 3. install
sudo make install