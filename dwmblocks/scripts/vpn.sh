#!/bin/sh

if [ `pgrep -x openvpn` ]; then 
	echo "  VPN "; 
fi
