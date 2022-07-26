#!/bin/sh
([ 0 -eq $1 ] && exit 0) || (./impair.py $(($1-1)); exit $?)
