#!/bin/bash

# simple script for switch workspace with mouse/touchpad (using vdesk)
# created by diws

checkws=$(vdesk)
action=$(($checkws-1))
minws=1
maxws=5

if [ ${checkws} -gt $minws ] ; then
        vdesk ${action}
        notify-send Workspace" "${action}
elif [ ${checkws} -eq $minws ] ; then
        vdesk ${maxws}
        notify-send Workspace" "${maxws}
else
        :
fi
