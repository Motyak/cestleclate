#!/bin/sh
echo "$(transpiler Repas.h)\n\n$(tail -n+2 serveur.cpp | transpiler)"
