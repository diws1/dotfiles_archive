#!/bin/bash

# simple scripts for volume (with pipewire)
# created by diws

Icon=""
Volume=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{ print $2*100"%" }')

echo "$Icon $Volume"
