#!/bin/sh
SRC=$1

[ -z $SRC ] &&
[ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ] &&
SRC="$(ls *.cpp)"

grep -zoP 'int main\(.*\)(?:.|\n)*{((?:.|\n)*)}\n?' $SRC
