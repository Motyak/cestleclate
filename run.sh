#!/bin/sh
TMP=/tmp/$(date +%s) && 
mkdir -p $TMP &&
curl -sSo $TMP/c.cpp https://raw.githubusercontent.com/Motyak/cestleclate/master/c.cpp && 
g++ -o $TMP/a.out $TMP/c.cpp &&
$TMP/a.out
rm -rf $TMP
