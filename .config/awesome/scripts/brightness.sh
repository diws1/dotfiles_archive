#!/bin/bash

# simple script for brightness (with brightnessctl)
# created by diws

#Icon=""
Icon="🔅"
Brightness=$(brightnessctl | awk 'NR==2{print$4}' | sed s/'('// | sed s/')'//)

echo "$Icon $Brightness  "



