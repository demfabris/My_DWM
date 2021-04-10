#!/bin/bash

# DWM Autostart script

# Keyboard config
# xset +fp /home/fabricio7p/.local/share/fonts
# xset fp rehash
xset r rate 300 50
setxkbmap -model abnt2 -layout br -variant abnt2

# Make screen not so unbearable
redshift -P -O 5500;

# Composition
picom &

# Notifications
dunst &

# Wallpaper
# feh --bg-scale ~/Pictures/redblocks.jpg
hsetroot -solid "#131f26" # oceanic next
# hsetroot -solid "#23252e" # onedark
# hsetroot -solid "#076678" # gruvbox

# Import statusbar features
dwmblocks &

# exec autolock display
# xautolock -time 10
