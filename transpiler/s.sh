#!/bin/sh

SRC=$1
if [ -z $SRC ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	SRC="$(ls *.cpp)"
fi

# remove shebang
perl -pe 's/^#!.*\n(?:.*)/$1/' $SRC |

# substitute prices with currency in front
perl -pe 's/\$([0-9]+(?:\.[0-9]{1,2})?)/Prix{'\''\$'\'', $1}/g' |
# substitute prices with currency in back
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)€/Prix{L'\''€'\'', $1}/g' |

# substitute percentages
perl -pe 's/([0-9]+(?:\.[0-9]{1,2})?)%/Pourcentage{$1}/g' |

# subsitute milliseconds
perl -pe 's/([0-9]+(?:\.[0-9]+)?)ms/std::chrono::milliseconds($1)/g' |
# subsitute seconds
perl -pe 's/([0-9]+(?:\.[0-9]+)?)s/std::chrono::seconds($1)/g' |
# subsitute minutes
perl -pe 's/([0-9]+(?:\.[0-9]+)?)m/std::chrono::minutes($1)/g' |
# subsitute hours
perl -pe 's/([0-9]+(?:\.[0-9]+)?)h/std::chrono::hours($1)/g'
