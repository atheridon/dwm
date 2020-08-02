#!/bin/sh

[ $(pamixer --get-mute) = true ] && echo " 婢 " && exit

vol="$(pamixer --get-volume)"

if [ "$vol" -gt "70" ]; then
	icon=" "
elif [ "$vol" -gt "30"]; then
	icon="墳 "
elif [ "$vol" -gt "0" ]; then
	icon="奔 "
else
	icon=" "
fi

echo " $icon$vol% "
