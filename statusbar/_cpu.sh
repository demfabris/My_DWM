#!/bin/bash

COOL="^c#6699cc^"
CI=""
WARN="^c#fac863^"
WI=""
DANGER="^c#ec5f67^"
DI=" "

# Fetching current CPU state
TEMP="$(sensors | grep -e 'Package id 0' | awk '{print $4}' | sed 's/[^0-9\.]//g;s/\.[0-9]//g')"

[ $TEMP -lt 30 ] && STATE="${COOL}" && TSTATE="${CI}"
[ $TEMP -gt 30 ] && [ $TEMP -lt 70 ] && STATE="${WARN}" && TSTATE="${WI}"
[ $TEMP -ge 70 ] && STATE="${DANGER}" && TSTATE="${DI}"

echo "${STATE} ${TEMP}°C ${TSTATE} ^d^"
