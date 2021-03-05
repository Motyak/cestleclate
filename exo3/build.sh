#!/bin/bash
for prog in client serveur
do
    ( echo "$(< Repas.h)" && echo "$(tail -n+2 c.cpp)" ) |
    transpiler |
    g++ -x c++ -std=c++17 -D $prog -o $prog -
done