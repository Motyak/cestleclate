#!/bin/sh
OUT=$RANDOM
SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi
#-x allows us to pass a str instead of file..
#..by process substitution
g++ -x c++ -I "$(pwd)" -o /tmp/$OUT $SRC $@
if [ -f /tmp/$OUT ]
then
	/tmp/$OUT
	rm /tmp/$OUT
fi