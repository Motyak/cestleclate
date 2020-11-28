#!/bin/sh
sudo mkdir -p /opt/cplusplus
sudo curl -sSo /opt/cplusplus/s.sh https://raw.githubusercontent.com/Motyak/cestleclate/master/cplusplus/s.sh
sudo chmod +x /opt/cplusplus/s.sh
sudo ln -s /opt/cplusplus/s.sh /bin/cplusplus
