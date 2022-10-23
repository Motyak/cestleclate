#!/bin/bash

previous_chrono=$(< chrono.txt)
current_chrono=$(date +'%s.%3N')
diff=$(echo "$current_chrono - $previous_chrono" | bc -l)

echo "$current_chrono" > chrono.txt
echo "$diff" >> times.txt
