#!/bin/bash
for prog in client serveur
do
    ( echo "$(< Repas.h)" && echo "$(tail -n+2 $prog.cpp)" ) |
    transpiler |
    g++ -x c++ -std=c++17 -o $prog -
done