gcc c.c -Wall -o meter
./chrono_start.sh; ./meter | ./on_change.sh "./chrono_split.sh && ./update_screen.sh"
