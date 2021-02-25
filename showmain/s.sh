#!/bin/sh
if [ $# -ne 1 ] && [ $(ls -l *.cpp 2>/dev/null | wc -l) = "1" ]
then
	grep -zoP 'int main\(.*\)(?:.|\n)*{((?:.|\n)*)}' "$(ls *.cpp)"
	echo ""
else
	for src in $@
	do
		echo "\e[35m$src\e[0m:"
		grep -zoP 'int main\(.*\)(?:.|\n)*{((?:.|\n)*)}' $src
		echo ""
	done
fi
