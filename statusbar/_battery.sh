#!/bin/bash

# Battery stuff

CAP="$(cat /sys/class/power_supply/BAT0/capacity)"
STATUS="$(cat /sys/class/power_supply/BAT0/status)"
STATE="^c#d4bfff^"

if [ "$STATUS" = "Discharging" ]; then
    if [ "$CAP" -ge 90 ]; then
        ICON=""; STATE="^c#c2d94c^"
    elif [ "$CAP" -lt 90 ]; then
        ICON=""; STATE="^c#c2d94c^"
    elif [ "$CAP" -lt 80 ]; then
        ICON=""; STATE="^c#c2d94c^"
    elif [ "$CAP" -lt 70 ]; then
        ICON=""; STATE="^c#e6b450^"
    elif [ "$CAP" -lt 60 ]; then
        ICON=""; STATE="^c#e6b450^"
    elif [ "$CAP" -lt 50 ]; then
        ICON=""; STATE="^c#e6b450^"
    elif [ "$CAP" -lt 40 ]; then
        ICON=""; STATE="^c#f07178^"
    elif [ "$CAP" -lt 30 ]; then
        ICON=""; STATE="^c#f07178^"
    elif [ "$CAP" -lt 20 ]; then
        ICON=""; STATE="^c#f07178^"
    else
        ICON=""; STATE="^c#f07178^"
    fi
elif [ "$STATUS" = "Not charging"  ]; then
    ICON=""

elif [ "$STATUS" = "Charging" ]; then
    ICON=""

elif [ "$STATUS" = "Full" ]; then
    ICON=""

elif [ "$STATUS" = "Unknown" ]; then
    ICON=""
fi

echo "${STATE} ${CAP}% ${ICON} ^d^"
