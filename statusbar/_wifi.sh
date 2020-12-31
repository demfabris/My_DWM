#!/bin/bash

# Wifi SSID and strengh

STR="$(grep wlan0 /proc/net/wireless | awk '{print $4}' | sed 's/[^0-9]//g')"
STR=$((STR-30))
SSID="$(iw dev | grep ssid | awk '{print $2}')"
ISTATE="^c#98c379^"

[ "$STR" -lt 35 ] && ICON=" " && ISTATE="^c#98c379^"
[ "$STR" -ge 35 ] && ICON="說" && ISTATE="^c#e5c07b^"
[ "$STR" -ge 55 ] && ICON="罹" && ISTATE="^c#d19a66^"

curl www.google.com.br &>/dev/null || ICON=" " ISTATE="^c#be5046^"

[ -z $SSID ] && SSID="off" && ICON="ﲁ " && ISTATE="^c#be5046^"

echo "^c#282828^${ISTATE} ${SSID} ${ICON} ^d^"
