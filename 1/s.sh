#!/bin/sh
OUT=$(date +%s)
SRC=$1
if [ $(ls -l *.cpp | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi
g++ -o /tmp/$OUT $SRC
if [ -f /tmp/$OUT ]
then
	/tmp/$OUT
	rm /tmp/$OUT
fi
