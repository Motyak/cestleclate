#!/bin/sh
FILE=/tmp/$(date +%s) && 
wget -qO $FILE.c.cpp https://raw.githubusercontent.com/Motyak/cestleclate/master/c.cpp && 
g++ -o $FILE $FILE.c.cpp &&
$FILE
rm $FILE $FILE.c.cpp 2>/dev/null