#!/bin/bash

while true; do
    ./read_until_carriage_return.sh \
    && eval "$1"
done
