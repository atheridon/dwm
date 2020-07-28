//Modify this file to change what commands output to your statusbar, and recompile using the make command.


static const Block blocks[] = {
	/*Icon*/	/*Command*/							/*Update Interval*/	/*Update Signal*/
	{"", 		"~/owncloud/Linux/dwm/dwmblocks/scripts/weather.sh",		3600,			0},
	{"", 		"~/owncloud/Linux/dwm/dwmblocks/scripts/vpn.sh",		5,			0},
	{"", 		"~/owncloud/Linux/dwm/dwmblocks/scripts/network.sh",		5,			0},
	{"", 		"~/owncloud/Linux/dwm/dwmblocks/scripts/audio.sh",		0,			1},
	{"", 		"~/owncloud/Linux/dwm/dwmblocks/scripts/xbacklight.sh",		0,			2},
	{"", 		"~/owncloud/Linux/dwm/dwmblocks/scripts/battery.sh",		5,			0},
	{"", 		"~/owncloud/Linux/dwm/dwmblocks/scripts/date.sh",		5,			0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
