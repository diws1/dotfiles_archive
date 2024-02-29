#!/bin/bash

# simple scripts for move window on another workspace (with xdotool, xwininfo)
# just replace number on line 2 and 4
# created by diws inspired by Graham

windowid=$(xdotool click 1 | xwininfo | awk NR==6'{print$4}')
vdesk 5 ${windowid}

notify-send 'Move to' 'workspace 5'
