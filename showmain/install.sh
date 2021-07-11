#!/bin/sh
sudo rm -rf /opt/showmain 2> /dev/null
sudo mkdir -p /opt/showmain
sudo curl -sSo /opt/showmain/s.sh https://raw.githubusercontent.com/Motyak/cestleclate/simple/showmain/s.sh
sudo chmod +x /opt/showmain/s.sh
sudo ln -fs /opt/showmain/s.sh /bin/showmain
