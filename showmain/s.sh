#!/bin/sh
OUT=$(date +%s)
SRC=$1
if [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi
grep -zoP 'int main\(\)(?:.|\n)*{((?:.|\n)*)}' $SRC | less
