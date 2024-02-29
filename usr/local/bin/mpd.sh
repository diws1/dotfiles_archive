#!/bin/bash

# simple script for mpd (with mpc)
# created by diws

Icon="♫"
Song=$(mpc current)
Stat=$(mpc status | awk 'NR==2{print $1}' | sed 's/\[//g' | sed 's/\]//g')

if [ "$Stat" = "playing" ] ; then
        echo "$Icon $Song"
elif [ "$Stat" = "paused" ] ; then
        echo "Paused $Icon $Song"
else
        echo ""
fi

