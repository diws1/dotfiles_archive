#!/bin/bash

# simple script for network
# created by diws

Icon1=""
Icon2=""
Device=$(nmcli connection show | awk NR==2'{print $4}')
Name=$(nmcli connection show | awk NR==2'{print $1}')

if [ "$Device" = "wlp3s0" ] ; then
	echo "$Icon1 $Name"
elif [ " $Device" = "enp2s0" ] ; then
	echo "$Iocn2 $Name"
else
	echo ""
fi
