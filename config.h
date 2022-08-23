/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=9" };
static const char dmenufont[]       = "monospace:size=9";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char titlefgcolor[]			= "#bbbbbb";
static char titlebgcolor[]			= "#eeeeee";
static char titlebordercolor[]		= "#eeeeee";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	   [SchemeTitle]  = { titlefgcolor, titlebgcolor,  titlebordercolor },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "CM",		centeredmaster},
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define XF86MonBrightnessDown 0x1008ff03
#define XF86MonBrightnessUp 0x1008ff02
#define XF86AudioMute 0x1008ff12
#define XF86AudioLowerVolume 0x1008ff11
#define XF86AudioRaiseVolume 0x1008ff13
#define XF86AudioMicMute 0x1008ffb2
#define Print 0x0000ff61
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *scrlockercmd[] = { "slock", NULL };
static const char *screenshotcmd[] = { "screenshot", NULL };
static const char *brightnessupcmd[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brightnessdowncmd[] = { "brightnessctl", "set", "10%-", NULL };
static const char *volumeraisecmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *volumelowercmd[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL  };
static const char *volumetogglecmd[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *mictogglecmd[] = { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };
static const char *musicpausecmd[] = { "playerctl", "play-pause", NULL };
static const char *musicstopcmd[] = { "playerctl", "play-pause", NULL };
static const char *musicprevcmd[] = { "playerctl", "previous", NULL };
static const char *musicnextcmd[] = { "playerctl", "next", NULL };
static const char *cyclemonitors[] = { "autorandr", "--cycle", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_Tab,    swapfocus,       },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ ALTKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ ALTKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ ALTKEY|ControlMask,          	XK_minus,  setgaps,        {.i = -1 } },
	{ ALTKEY|ControlMask,          	XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_f,      togglefullscr,  {0} },

	/* Layout manipulation */
	{ MODKEY,           			XK_space,  cyclelayout,    {.i = +1 } },

	/* Switching between monitors */
	{ MODKEY,           			XK_p,      spawn,          { .v = cyclemonitors } },
    { MODKEY|ShiftMask,             XK_h,  	   focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_o,      tagmon,         {.i = +1 } },

	/* Apps */
	{ MODKEY,						XK_n,	   spawn,		   SHCMD("st -e lf") },
	{ MODKEY,						XK_q,	   spawn,		   SHCMD("$BROWSER") },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
    { ALTKEY|MODKEY,                XK_l,      spawn,          {.v = scrlockercmd } },

    /* HotKeys */
    { 0,                            Print,                  spawn,  {.v = screenshotcmd } },
    { 0,                            XF86MonBrightnessDown,  spawn,  {.v = brightnessdowncmd } },
    { 0,                            XF86MonBrightnessUp,    spawn,  {.v = brightnessupcmd } },
    { 0,                            XF86AudioMute,          spawn,  {.v = volumetogglecmd } },
    { 0,                            XF86AudioRaiseVolume,   spawn,  {.v = volumeraisecmd } },
    { 0,                            XF86AudioLowerVolume,   spawn,  {.v = volumelowercmd } },
    { 0,                            XF86AudioMicMute,       spawn,  {.v = mictogglecmd } },
    { ALTKEY,                       XK_m,                   spawn,  {.v = volumetogglecmd } },
    { ALTKEY,                       XK_Up,                  spawn,  {.v = volumeraisecmd } },
    { ALTKEY,                       XK_Down,                spawn,  {.v = volumelowercmd } },

    /* Music/Video players */
    { ALTKEY|ControlMask,           XK_Left,   spawn,          {.v = musicprevcmd } },
    { ALTKEY|ControlMask,           XK_Up,     spawn,          {.v = musicpausecmd } },
    { ALTKEY|ControlMask,           XK_Right,  spawn,          {.v = musicnextcmd } },
    { ALTKEY|ControlMask,           XK_Down,   spawn,          {.v = musicstopcmd } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* DWM restart quit */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,           XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
};

