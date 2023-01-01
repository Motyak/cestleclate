#!/usr/bin/env bash

set -Eeuo pipefail

trap 'exit 1' ERR
trap clean_and_exit EXIT
function clean_and_exit {
    local exit_code=$?
    pkill -P $$ || true # terminate subprocesses, if any
    exit $exit_code
}

function print {
    local msg=$*

    echo -ne "\r${msg// LF/\\n}"
}

function countdown {
    local nb_of_seconds=$1

    ret=$(seq -s ' ' 1 $nb_of_seconds | rev)
    for i in $ret; do print $i; sleep 1; done
}

function rand {
    local min=$1
    local max=$2

    WEB_RAND_CMD='curl -s "https://www.random.org/integers/?num=1&min=$min&max=$max&col=1&base=10&format=plain&rnd=new"'
    LOCAL_RAND_CMD='echo -n $((RANDOM % (max + 1) + min))'

    ret=$(eval "$WEB_RAND_CMD || $LOCAL_RAND_CMD")
    echo -n "$ret"
}

declare -A winner

function pick_a_winner {
    local file=$1

    ret=$(perl -pe 's/^\s*$//' "$file")
    [ "$ret" != "" ] || {
        >&2 echo "input file '$file' is empty"
        exit 1
    }

    readarray -t choices <<< "$ret"
    
    min=0
    max=$((${#choices[@]} - 1)) # arr size -1
    random_i=$(rand $min $max)

    winner["$file"]=${choices[$random_i]}
}

countdown 5 &

INPUT_FILES=${*:-*.in}
for file in $INPUT_FILES; do
    pick_a_winner "$file"
done

wait

for key in "${!winner[@]}"; do
    print "${key%.*}:${winner[$key]}" LF
done
