#!/usr/bin/env bash

set -Eeuo pipefail

function print {
    local msg=$*

    echo -ne "\r${msg//LF/\\n}"
}

function countdown {
    local nb_of_seconds=$1

    ret=$(seq -s ' ' 1 $nb_of_seconds | rev)
    for i in $ret; do print $i; sleep 1; done
}

function rand {
    local min=$1;
    local max=$2;

    ret=$(curl -s "https://www.random.org/integers/?num=1&min=$min&max=$max&col=1&base=10&format=plain&rnd=new")
    echo -n "$ret"
}

INPUT_FILE="input.txt"

ret=$(perl -pe 's/^\s*$//' $INPUT_FILE)
[ "$ret" != "" ] || {
    >&2 echo "input file is empty"
    exit 1
}

readarray -t choices <<< "$ret"

countdown 5 &

min=0
max=$((${#choices[@]} - 1)) # arr size -1

random_i=$(rand $min $max)

winner=${choices[$random_i]}

wait
print $winner LF; 
