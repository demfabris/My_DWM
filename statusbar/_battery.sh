#!/bin/bash

# Battery stuff

CAP="$(cat /sys/class/power_supply/BAT0/capacity)"
STATUS="$(cat /sys/class/power_supply/BAT0/status)"
STATE="^c#c678dd^"


if [ "$STATUS" = "Discharging" ]; then
    if [ "$CAP" -ge 90 ]; then
        ICON=""; STATE="^c#98c379^"
    elif [ "$CAP" -lt 90 ]; then
        ICON=""; STATE="^c#98c379^"
    elif [ "$CAP" -lt 80 ]; then
        ICON=""; STATE="^c#98c379^"
    elif [ "$CAP" -lt 70 ]; then
        ICON=""; STATE="^c#e5c07b^"
    elif [ "$CAP" -lt 60 ]; then
        ICON=""; STATE="^c#e5c07b^"
    elif [ "$CAP" -lt 50 ]; then
        ICON=""; STATE="^c#e5c07b^"
    elif [ "$CAP" -lt 40 ]; then
        ICON=""; STATE="^c#d19a66^"
    elif [ "$CAP" -lt 30 ]; then
        ICON=""; STATE="^c#e06c75^"
    elif [ "$CAP" -lt 20 ]; then
        ICON=""; STATE="^c#e06c75^"
    else
        ICON=""; STATE="^c#e06c75^"
    fi
elif [ "$STATUS" = "Not charging"  ]; then
    ICON=""

elif [ "$STATUS" = "Charging" ]; then
    ICON=""

elif [ "$STATUS" = "Full" ]; then
    ICON=""
fi

echo "${STATE} ${CAP}% ${ICON} ^d^"
