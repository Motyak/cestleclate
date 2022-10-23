#!/bin/bash

[ -f times.txt ] && rm times.txt
date +'%s.%3N' > chrono.txt
