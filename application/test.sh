#!/bin/zsh

exec $TERM -e "./server/bin/Debug/server" &

sleep 3

exec $TERM -e "./agent/bin/Debug/agent" &

sleep 5

exec $TERM -e "./client/bin/Debug/konsola -demo" &

