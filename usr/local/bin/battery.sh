#!/bin/bash

# simple script for battery
# created by diws

Icon1=""
Icon2=""
Icon3=""
Battery=$(cat /sys/class/power_supply/BAT0/capacity)
Midle="70"
Low="20"

if [ "$Battery" -le "$Low" ] ; then
        echo "$Icon3 $Battery%"
elif [ "$Battery" -le "$Midle" ] ; then
        echo "$Icon2 $Battery%"
else
        echo "$Icon1 $Battery%"
fi
