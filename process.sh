#! /bin/bash

while true; do
	clear
	PID=$(pgrep minishell)

	if [ -n "$PID" ];
	then
		ps -A | grep minishell
		ps -A | grep minishell | wc -l
		sleep 2
	else
		echo "waiting for minishell to start..."
		sleep 3
	fi
done
