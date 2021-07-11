#!/bin/sh
sudo rm -rf /opt/cplusplus 2>/dev/null
sudo mkdir -p /opt/cplusplus
sudo curl -sSo /opt/cplusplus/s.sh https://raw.githubusercontent.com/Motyak/cestleclate/simple/cplusplus/s.sh
sudo chmod +x /opt/cplusplus/s.sh
sudo ln -fs /opt/cplusplus/s.sh /bin/cplusplus
