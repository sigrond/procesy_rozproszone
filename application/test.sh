#!/bin/zsh

exec $TERM -e "./server/bin/Debug/server" &

exec $TERM -e "./agent/bin/Debug/agent" &

exec $TERM -e "./client/bin/Debug/konsola -demo" &

