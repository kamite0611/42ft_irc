#!/bin/bash

pid=0

while true; do
    pid=$(pgrep ircserv)
    if [ -n "$pid" ]; then
        break
    fi
    sleep 1
done

while true; do
    leaks -q $pid
    sleep 1
done