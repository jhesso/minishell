#! /bin/bash

while true
do
	if pgrep "minishell" > /dev/null;
	then
		clear
		leaks minishell
	else
		echo "waiting for minishell to start..."
	fi
	sleep 3
done
