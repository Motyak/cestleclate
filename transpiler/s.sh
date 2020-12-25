#!/bin/sh
SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi

# pattern regex représentant un prix

# pattern regex représentant un pourcentage

# afficher le contenu du fichier src, remplacer les matchs

cat $1
