#!/usr/bin/env python3
from sys import exit, argv
from subprocess import run as exec
exit(exec(f'! ./pair.sh {argv[1]}', shell=True).returncode)
