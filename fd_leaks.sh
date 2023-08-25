#! /bin/bash

# Colors!
RED="\033[0;31m"
RESET="\033[0m"

COUNT=0
while true
do
    PID=$(pgrep minishell)

    if [ -n "$PID" ];
    then
		clear
        lsof -p $PID
		NB_FILES=$(lsof -p $PID | wc -l)
		echo "amount of files: $NB_FILES"
		if [ "$OLD_NB" != "$NB_FILES" ];
		then
			if [ $COUNT != 0 ];
			then
				echo "${RED}potential fd leaks!${RESET}"
			fi
			OLD_NB=$NB_FILES
		fi
		((COUNT++))
		sleep 5
    else
		echo "waiting for minishell to start..."
        sleep 3
    fi
done
