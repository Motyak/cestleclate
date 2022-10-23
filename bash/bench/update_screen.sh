#!/bin/bash

it=0
sum=0
while read val; do
    sum=$(echo "$sum + $val" | bc -l)
    it=$((it+1))
done < times.txt

avg=$(echo "scale=3; $sum / $it" | bc -l)

# e.g.: ''' it: 3 ; avg: 6.123s'''
printf " it: %s ; avg: %ss\r" $it $avg
