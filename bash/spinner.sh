#!/usr/bin/env bash

# e.g.: "abc" => "a b c"
function split {
    fold -w1 <<<$1 | paste -sd' '
}

# e.g.: wait_for 1s ; wait_for 500ms
function wait_for {
    local t=${1%ms}
    if [ "$t" == "$1" ]; then
        sleep_val=${t%s}
    else
        sleep_val=$(bc <<<"scale=3; $t / 1000")
    fi
    sleep $sleep_val
}

# e.g.: animate '-\|/' 500ms
function animate {
    local spinner_states=$1
    local delta_t=$2

    for state in $(split $spinner_states); do
        printf "%s\r" $state
        wait_for $delta_t
    done
}

animate $@
