#!/bin/bash

windowid=$(xdotool click 1 | xwininfo | awk NR==6'{print$4}')
vdesk 1 ${windowid}

notify-send 'Move to' 'workspace 1'
