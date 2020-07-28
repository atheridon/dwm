#!/bin/sh

date="$(date +"%a, %B %d %l:%M%p" | sed 's/  / /g')"
icon=" "

echo " $icon$date "
