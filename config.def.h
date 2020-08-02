/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     	/* 0 means no systray */
static const unsigned int gappih    = 25;	/* horiz inner gap between windows */
static const unsigned int gappiv    = 25;	/* vert inner gap between windows */
static const unsigned int gappoh    = 25;	/* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 25; 	/* vert outer gap between windows and screen edge */
static const int smartgaps	    = 0;	/* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "IBMPlexMono:semibold:size=12" };
static const char dmenufont[]       = "IBMPlexMono:semibold:size=12";
static const char dmenubg[]         = "#000000";
static const char dmenuprompt[]     = "Run:";
static const char col_black[]	    = "#000000";
static const char col_gray1[]       = "#444444";
static const char col_gray2[]       = "#222222";
static const char col_white[]	    = "#ffffff";
static const char col_yellow[]	    = "#ffff00";
static const char col_blue[]	    = "#0356fc";
static const char col_green[]	    = "#1eff00";
static const unsigned int baralpha  = 0xff;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_gray1 },
	[SchemeSel]  = { col_black, col_yellow, col_yellow },
};
static const unsigned int alphas[][3]	= {
	/*		fg	bg	border	*/
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "microsoft teams - preview", NULL, NULL, 0,  	  1,          0,           0,        -1 },
	{ "Gimp",    NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st-256color", NULL, NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#include <X11/XF86keysym.h>

#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-g", "3", "-l", "10", "-fn", dmenufont, "-nb", dmenubg, "-p", dmenuprompt, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ 0,                    	XF86XK_AudioRaiseVolume,   spawn,  SHCMD("/usr/bin/amixer -q set Master 5%+ unmute; pkill -RTMIN+1 dwmblocks") },
        { 0,                    	XF86XK_AudioLowerVolume,   spawn,  SHCMD("/usr/bin/amixer -q set Master 5%- unmute; pkill -RTMIN+1 dwmblocks") },
        { 0,                    	XF86XK_AudioMute,          spawn,  SHCMD("/usr/bin/amixer -q set Master toggle; pkill -RTMIN+1 dwmblocks") },
        { 0,                    	XF86XK_MonBrightnessUp,    spawn,  SHCMD("/usr/bin/xbacklight -inc 2; pkill -RTMIN+2 dwmblocks") },
        { 0,                    	XF86XK_MonBrightnessDown,  spawn,  SHCMD("/usr/bin/xbacklight -dec 2; pkill -RTMIN+2 dwmblocks") },
	{ MODKEY|ShiftMask,		XK_e,	   spawn,	   SHCMD("~/owncloud/Linux/scripts/pdmenu") },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,	   SHCMD("~/owncloud/Linux/scripts/xdisplay") },
	{ MODKEY|ControlMask,		XK_l,	   spawn,	   SHCMD("~/owncloud/Linux/scripts/lock") },
	{ MODKEY,			XK_e,	   spawn,	   SHCMD("st -e ranger") },
	{ 0,				XK_Print,  spawn,	   SHCMD("scrot -q 100 ~/tmp/%b%d::%H%M%S.png && notify-send 'Screenshot taken!' && sxiv -t ~/tmp/") },
	{ ShiftMask,			XK_Print,  spawn,	   SHCMD("sleep 0.2; scrot -q 100 -s ~/tmp/%b%d::%H%M%S.png && notify-send 'Screenshot taken!' && sxiv -t 9999 ~/tmp/") },

	{ MODKEY,                       XK_numbersign,  togglescratch,     {.v = scratchpadcmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
        { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
        { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +10 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -10 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	/*{ MODKEY|Mod4Mask|ShiftMask,	XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },*/
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,		XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,			XK_r,	   resetlayout,    {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,             		XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_BackSpace, quit,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

