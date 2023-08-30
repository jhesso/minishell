#! /bin/bash

# while true
# do
# 	clear
# 	cat log.txt
# 	read -n 1
# done

FILE_TO_WATCH="log.txt"
last_modified=$(stat -f "%m" "$FILE_TO_WATCH")

while true; do
    current_modified=$(stat -f "%m" "$FILE_TO_WATCH")
    if [[ "$current_modified" -gt "$last_modified" ]]; then
		clear
        cat "$FILE_TO_WATCH"
        last_modified="$current_modified"
    fi
    sleep 1
done

