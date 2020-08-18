#!/bin/bash

# Display date

echo "^c#83a598^ $(date +%x)  ^d^ "

case $BLOCK_BUTTON in
    1) notify-send "$(cal)" ;;
    2) notify-send "AOSDKASD" ;;
esac
