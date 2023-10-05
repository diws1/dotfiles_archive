#!/bin/bash

# simple script for temperature
# created by diws

#Icon1=""
#Icon2=""
#Icon3=""
Icon="⛄"
Temperature=$(cat /sys/class/thermal/thermal_zone0/temp | awk '{print $1/1000}')
Midle="70"
Dangerous="85"

if [ "$Temperature" -ge "$Dangerous" ] ; then
	echo "$Icon $Temperature°C  "
elif [ "$Temperature" -ge "$Midle" ] ; then
	echo "$Icon $Temperature°C  "
else
	echo "$Icon $Temperature°C  "
fi



