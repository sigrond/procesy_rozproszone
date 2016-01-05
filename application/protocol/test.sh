#!/bin/zsh

if [ "$#" -ne 0 ]; then

	exec $TERM -e "./server $1" &

	for i in {1..$1}; do
		exec $TERM -e "./client $i" &
	done
fi

