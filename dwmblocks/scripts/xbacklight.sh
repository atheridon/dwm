#!/bin/sh

perc="$(xbacklight | sed 's/\\..*//')"
perc_int=${perc/\.*/}

if [ "$perc_int" -eq "100" ]; then
	icon="🌑 "
elif [ "$perc_int" -gt "50" ]; then
	icon="🌒 "
elif [ "$perc_int" -gt "20" ]; then
	icon="🌓 "
elif [ "$perc_int" -gt "0" ]; then
	icon="🌔 "
elif [ "$perc_int" -le "0" ]; then
	icon="🌕 "
fi

echo " $icon$perc_int% "
