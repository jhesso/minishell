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
		if [ -n "$OLD_NB" ] && [ "$OLD_NB" -lt "$NB_FILES" ];
		then
			if [ $COUNT -ne 0 ];
			then
				echo "${RED}potential fd leaks!${RESET}"
				if [ "$HOSTNAME" = "jhesso-arch" ];
				then
					dunstify --urgency=critical "Potential FD leaks!" "potential fd leaks!"
				fi
			fi
		fi
		OLD_NB=$NB_FILES
		((COUNT++))
		sleep 3
    else
		echo "waiting for minishell to start..."
        sleep 3
    fi
done
