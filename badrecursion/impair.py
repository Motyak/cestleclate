#!/usr/bin/env python3
from sys import exit, argv
from subprocess import call
exit(call(['./pair.sh', argv[1]]) ^ 1)
