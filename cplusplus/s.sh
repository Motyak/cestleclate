#!/bin/sh
OUT="$(od -An -N2 -i /dev/random | xargs)"
SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi
#-x allows us to pass a str instead of file..
#..by process substitution
g++ -x c++ -std=c++17 -I "$(pwd)" -o /tmp/$OUT $SRC $@
if [ -f /tmp/$OUT ]
then
	/tmp/$OUT
	rm /tmp/$OUT
fi