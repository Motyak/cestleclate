#!/bin/bash
# import definitions from header.hpp (use as $HEADER)
HEADER="cat $(echo $(dirname $(readlink -f $0))/header.hpp)"

SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
    SRC="$(ls *.cpp)"
fi

# substitute shebang with header
X=$($HEADER) perl -0pe 's/^#!.*\n\n?((.|\n)*)/$ENV{X}\n\n$1/g' $SRC |

# make void functions return 'nada' (custom type)
perl -pe 's/void ([a-zA-Z][a-zA-Z0-9_]*\(.*\))/nada $1/g' |

# substitute prices with currency in front
perl -pe 's/\$([0-9]+(?:\.[0-9]{1,2})?)/Prix{'\''\$'\'', $1}/g' |
# substitute prices with currency in back
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)€/Prix{L'\''€'\'', $1}/g' |
# substitute percentages
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)%/Pourcentage{$1}/g'
