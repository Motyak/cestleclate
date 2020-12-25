#!/bin/sh
SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi

# substitute prices with currency in front
perl -pe 's/\$([0-9]+(?:\.[0-9]{1,2})?)/Prix{'\''\$'\'', $1}/g' $SRC |
# substitute prices with currency in back
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)€/Prix{'\''\€'\'', $1}/g' |
# substitute percentages
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)%/Pourcentage{$1}/g'
