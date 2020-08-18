#!/bin/bash

# DWM Autostart script

# Make screen not so unbearable
redshift -P -O 4500;

# Composition
picom &

# Notifications
dunst &

# Wallpaper
# feh --bg-scale ~/Pictures/city.jpg
hsetroot -solid "#076678"

# Import statusbar features
dwmblocks &
# exec ./statusbar/statusbar.sh &
