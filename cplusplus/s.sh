#!/bin/sh
OUT=$(date +%s)
SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi
#-x allows us to pass a str instead of file..
#..by process substitution
cat $SRC | tail -n+2 | g++ -x c++ -o /tmp/$OUT -
if [ -f /tmp/$OUT ]
then
	/tmp/$OUT
	rm /tmp/$OUT
fi
