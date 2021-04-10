#!/bin/bash

# Wifi SSID and strengh

STR="$(grep wlan0 /proc/net/wireless | awk '{print $4}' | sed 's/[^0-9]//g')"
STR=$((STR-30))
SSID="$(iw dev | grep ssid | awk '{print $2}')"
ISTATE="^c#99c794^"

[ "$STR" -lt 35 ] && ICON=" " && ISTATE="^c#99c794^"
[ "$STR" -ge 35 ] && ICON="說" && ISTATE="^c#fac863^"
[ "$STR" -ge 55 ] && ICON="罹 " && ISTATE="^c#f99157^"

curl www.google.com.br &>/dev/null || ICON=" " ISTATE="^c#f99157^"

[ -z $SSID ] && SSID="off" && ICON="ﲁ " && ISTATE="^c#ec5f67^"

echo "^c#282828^${ISTATE} ${SSID} ${ICON} ^d^"
