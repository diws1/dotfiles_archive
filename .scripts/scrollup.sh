#!/bin/bash

# simple script for switch workspace with mouse/touchpad (using vdesk)
# created by diws

checkws=$(vdesk)
action=$(($checkws+1))
minws=1
maxws=5

if [ ${checkws} -lt $maxws ] ; then
        vdesk ${action}
        notify-send Workspace" "${action}
elif [ ${checkws} -eq $maxws ] ; then
        vdesk ${minws}
        notify-send Workspace" "${minws}
else
        :
fi
