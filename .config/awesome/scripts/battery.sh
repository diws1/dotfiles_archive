#!/bin/bash

# simple script for battery
# created by diws

#Icon1=""
#Icon2=""
#Icon3=""
Icon="⚡"
Battery=$(cat /sys/class/power_supply/BAT0/capacity)
Midle="70"
Low="20"

if [ "$Battery" -le "$Low" ] ; then
        echo "$Icon $Battery%  "
elif [ "$Battery" -le "$Midle" ] ; then
        echo "$Icon $Battery%  "
else
        echo "$Icon $Battery%  "
fi
