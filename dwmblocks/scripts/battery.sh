#!/bin/sh

bat=`acpi -b | grep -P -o '[0-9]+(?=%)'`
bat_status=`acpi -b | cut -f 3 -d " "`

if [[ $bat_status == "Charging," || $bat_status == "Full," ]]; then
	icon=" "
else
	if [ "$bat" -gt 80 ]; then
		icon=" "
	elif [ "$bat" -gt 50 ]; then
		icon=" "
	elif [ "$bat" -gt 20 ]; then
		icon=" "
	elif [ "$bat" -gt 0 ]; then
		icon=" "
	else
		icon=" "
	fi
fi

echo " $icon$bat% "
