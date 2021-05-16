#!/bin/bash

# Wifi SSID and strengh

STR="$(grep wlan0 /proc/net/wireless | awk '{print $4}' | sed 's/[^0-9]//g')"
STR=$((STR-30))
SSID="$(iw dev | grep ssid | awk '{print $2}')"
ISTATE="^c#c2d94c^"

[ "$STR" -lt 35 ] && ICON=" " && ISTATE="^c#c2d94c^"
[ "$STR" -ge 35 ] && ICON="說" && ISTATE="^c#e6b450^"
[ "$STR" -ge 55 ] && ICON="罹 " && ISTATE="^c#ff8f40^"

curl www.google.com.br &>/dev/null || ICON=" " ISTATE="^c#ff8f40^"

[ -z $SSID ] && SSID="off" && ICON="ﲁ " && ISTATE="^c#f07178^"

echo "^c#282828^${ISTATE} ${SSID} ${ICON} ^d^"
