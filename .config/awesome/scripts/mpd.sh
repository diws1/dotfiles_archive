#!/bin/bash

# simple script for mpd (with mpc)
# created by diws

Icon1=" 🤪 🎵"
Icon2=" 🤬 🎵"
Song=$(mpc current)
Stat=$(mpc status | awk 'NR==2{print $1}' | sed 's/\[//g' | sed 's/\]//g')

if [ "$Stat" = "playing" ] ; then
	echo "$Icon1 $Song  "
elif [ "$Stat" = "paused" ] ; then
	echo "$Icon2 $Song  "
else
	echo ""
fi
