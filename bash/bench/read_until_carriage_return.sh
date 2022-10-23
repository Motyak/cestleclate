#!/bin/bash

read -n1 cur_char
until [ $cur_char == $'\r' ]; do
    read -n1 cur_char
done
