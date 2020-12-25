#!/bin/sh
sudo mkdir -p /opt/transpiler
sudo curl -sSo /opt/transpiler/s.sh https://raw.githubusercontent.com/Motyak/cestleclate/master/transpiler/s.sh
sudo chmod +x /opt/transpiler/s.sh
sudo ln -fs /opt/transpiler/s.sh /bin/transpiler
