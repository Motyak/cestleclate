#!/bin/sh
SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi

# substiture prices with currency in front
perl -pe 's/\$([0-9]+(?:\.[0-9]{1,2})?)/Prix{'\''\$'\'', $1}/g' $SRC |
# substiture prices with currency in back
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)€/Prix{'\''\€'\'', $1}/g' |
# substiture percentages
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)%/Pourcentage{$1}/g'
