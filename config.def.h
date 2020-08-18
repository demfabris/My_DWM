/* See LICENSE file for copyright and license details. */
#include "gaplessgrid.c"

/* appearance */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 20;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int tiledraise  = 1;    /* 1 means raise tiled windows when focused */

static const char *fonts[]          = { "Inconsolata Nerd Font:size=15:antialias=true:autohint=true", };
                                        /* "Inconsolata Nerd Font:size=16:antialias=true:autohint=true"}; */
static const char dmenufont[]       = "Product Sans:size=13:antialias=true:autohint=true";

// gruvbox
static const char col_gb_bg[]        = "#282828";
static const char col_gb_fg[]        = "#ebdbb2";

static const char col_gb_red1[]     = "#cc241d";
static const char col_gb_red2[]     = "#fb4934";

static const char col_gb_green1[]   = "#98971a";
static const char col_gb_green2[]   = "#b8bb26";

static const char col_gb_yellow1[]  = "#d79921";
static const char col_gb_yellow2[]  = "#fabd2f";

static const char col_gb_blue1[]    = "#458588";
static const char col_gb_blue2[]    = "#83a598";

static const char col_gb_purple1[]  = "#b16286";
static const char col_gb_purple2[]  = "#83869b";

static const char col_gb_aqua1[]    = "#689d6a";
static const char col_gb_aqua2[]    = "#8ec07c";

static const char col_gb_gray1[]    = "#a89984";
static const char col_gb_gray2[]    = "#928374";
static const char col_gb_gray3[]    = "#665c54";

static const char col_gb_orange1[]  = "#d65d0e";
static const char col_gb_orange2[]  = "#fe8019";
// gruvbox

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]     = { col_gb_gray2,   col_gb_bg,      col_gb_bg },
	[SchemeSel]      = { col_gb_orange2, col_gb_bg,      col_gb_gray1 },
	[SchemeSel2]     = { col_gb_fg,      col_gb_bg,      col_gb_bg },
	[SchemeUrgent]   = { col_gb_fg,      col_gb_bg,      col_gb_bg },
	[SchemeTitle]    = { col_gb_fg,      col_gb_bg,      col_gb_bg },
	[SchemeLt]       = { col_gb_orange2, col_gb_bg,      col_gb_bg },
	[SchemeNotify]   = { col_gb_red1,    col_gb_bg,      col_gb_bg },
	[SchemeStatus]   = { col_gb_aqua2,   col_gb_bg,      col_gb_bg },
	[SchemeIndOff]   = { col_gb_green2,  col_gb_bg,      col_gb_bg },
	[SchemeIndOn]    = { col_gb_blue2,   col_gb_bg,      col_gb_bg },
};

/* tagging */
/* static const char *tags[] = { " ", "爵 ", " ", " "}; */
static const char *tags[] = { "", "", "", "", ""};
static const char *tagsalt[] = { "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "google-chrome",NULL,      NULL,       2,            0,           -1 },
	{ "st-256color", NULL,       NULL,       0,            1,           -1 },
	{ "Spotify",     NULL,       NULL,       0,            1,           -1 },
	{ "Discord",     NULL,       NULL,       1 << 4,       1,           -1 },
	{ "Nautilus",    NULL,       NULL,       0,            1,           -1 },
	{ "feh",         NULL,       NULL,       0,            1,           -1 },
	/* { NULL,       NULL,       "Cmus",     1 << 5,       0,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "﩯 ",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle }
	/* { "ﱖ",      gaplessgrid }, */
};

/* key definitions */
#define MODKEY Mod4Mask
#define SUPERMOD Mod4Mask|Mod1Mask
#define ALTMOD Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define PrintScreenDWM	    0x0000ff61

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL }; */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", "-g", "120x30", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("nautilus") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ 0,                    PrintScreenDWM,    spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_l,      spawn,          SHCMD("google-chrome-stable") },
	{ 0,			  XF86XK_AudioLowerVolume, spawn,          SHCMD("pulseaudio-ctl down 5 ; kill -44 $(pidof dwmblocks)") },
	{ 0,			  XF86XK_AudioRaiseVolume, spawn,          SHCMD("pulseaudio-ctl up 5 ; kill -44 $(pidof dwmblocks)") },
	{ 0,			  XF86XK_AudioMute,        spawn,          SHCMD("pulseaudio-ctl mute ; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ ALTMOD,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ ALTMOD|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },
	/* { MODKEY,                       XK_Return, zoom,           {0} }, */
	{ ALTMOD,                       XK_grave,  view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ ALTMOD|ShiftMask,             XK_Return, togglefullscr,  {0} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	/* { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} }, */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ ALTMOD,                       XK_Return, togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Right,  shiftview,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_Left,   shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_j,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

