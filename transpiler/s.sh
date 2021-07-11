#!/bin/bash
SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi
# every custom definitions must be appended to this variable
header=""

# add 'nada' type, as void but can be implicitly cast to bool as true
header="$header""struct nada\n{\n\toperator void() const {}\n\toperator bool() const { return true; }\n};\n"

# remove shebang
perl -pe 's/^#!.*\n\n?((.|\n)*)/$1/g' $SRC |

# make void functions return 'nada' (custom type)
perl -pe 's/void ([a-zA-Z][a-zA-Z0-9_]*\(.*\))/nada $1/g' |

# substitute prices with currency in front
perl -pe 's/\$([0-9]+(?:\.[0-9]{1,2})?)/Prix{'\''\$'\'', $1}/g' |
# substitute prices with currency in back
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)€/Prix{L'\''€'\'', $1}/g' |
# substitute percentages
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)%/Pourcentage{$1}/g' |

# replace source file header to add custom definitions
X=$(echo -e "$header") perl -0pe 's/(#include.*\n(?!#))(.*)/$1\n$ENV{X}\n$2/g'
