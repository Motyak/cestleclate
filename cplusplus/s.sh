#!/bin/bash
OUT="/tmp/$(od -An -N2 -i /dev/random | xargs)"
SRC=$1

[ -z $SRC ] && 
[ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ] &&
SRC="$(ls *.cpp)"

#-x allows us to pass a str instead of file..
#..by process substitution
g++ -x c++ -I "$(pwd)" -o $OUT $SRC ${@:2}

[ -f $OUT ] &&
($OUT; rm $OUT)
