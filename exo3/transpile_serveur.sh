#!/bin/sh
echo "$(transpiler Repas.h)\n$(tail -n+2 Repas.cpp)\n$(tail -n+2 serveur.cpp | transpiler)"
