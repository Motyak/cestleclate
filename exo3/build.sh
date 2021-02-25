#!/bin/sh
for prog in client serveur
do
    echo "$(cat Repas.h)\n$(tail -n+2 $prog.cpp)" |
    transpiler |
    g++ -x c++ -std=c++17 -o $prog -
done