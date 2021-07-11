#!/bin/bash
eval $(echo "$1" | SUBSTITUTE="$2" perl -pe 's/\$f/$ENV{SUBSTITUTE}/g')