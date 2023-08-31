#! /bin/bash

# while true
# do
# 	clear
# 	cat log.txt
# 	read -n 1
# done

FILE_TO_WATCH="log.txt"
if [[ "$(uname)" == "Darwin" ]]; then
    last_modified=$(stat -f "%m" "$FILE_TO_WATCH")
else
    last_modified=$(stat -c "%Y" "$FILE_TO_WATCH")
fi

while true; do
    if [[ "$(uname)" == "Darwin" ]]; then
        current_modified=$(stat -f "%m" "$FILE_TO_WATCH")
    else
        current_modified=$(stat -c "%Y" "$FILE_TO_WATCH")
    fi

    if [[ "$current_modified" -gt "$last_modified" ]]; then
        clear
        cat "$FILE_TO_WATCH"
        last_modified="$current_modified"
    fi
    sleep 1
done

