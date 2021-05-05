#!/bin/sh
sudo rm -rf /opt/shbang 2> /dev/null
sudo mkdir -p /opt/shbang
sudo curl -sSo /opt/shbang/s.sh https://raw.githubusercontent.com/Motyak/cestleclate/master/shbang/s.sh
sudo chmod +x /opt/shbang/s.sh
sudo ln -fs /opt/shbang/s.sh /bin/shbang
