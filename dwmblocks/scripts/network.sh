#!/bin/sh

case "$(cat /sys/class/net/w*/operstate 2>/dev/null)" in
	down) wifi="" ;;
	up) wifi="  $(iw wlp3s0 info | grep -Po '(?<=ssid ).*') $(ip -4 addr show wlp3s0 | grep -oP '(?<=inet\s)\d+(\.\d+){3}')" ;;
esac

case "$(cat /sys/class/net/e*/operstate 2>/dev/null)" in
	down) eth="" ;;
	up) eth="  $(ip -4 addr show enp4s0f1 | grep -oP '(?<=inet\s)\d+(\.\d+){3}')" ;;
esac

if [[ -z "$wifi" && -z "$eth" ]]; then
	exit
else
	echo "$wifi$eth "; 
fi
