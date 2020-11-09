#!/bin/sh

sudo mkdir -p /opt/cplusplus
sudo wget -O /opt/cplusplus/s.sh https://raw.githubusercontent.com/Motyak/cestleclate/master/cplusplus/s.sh
sudo chmod +x /opt/cplusplus/s.sh
sudo ln -s /opt/cplusplus/s.sh /bin/cplusplus
