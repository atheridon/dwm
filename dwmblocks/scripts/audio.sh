#!/bin/sh

[ $(pamixer --get-mute) = true ] && echo " 🔇 " && exit

vol="$(pamixer --get-volume)"

if [ "$vol" -gt "70" ]; then
	icon="🔊 "
elif [ "$vol" -gt "0" ]; then
	icon="🔉 "
else
	icon="🔈 "
fi

echo " $icon$vol% "
