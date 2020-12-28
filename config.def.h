/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;      /* border pixel of windows */
static const unsigned int snap      = 10;     /* snap pixel */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const int showbar            = 1;      /* 0 means no bar */
static const int topbar             = 1;      /* 0 means bottom bar */
static const int user_bh            = 35;     /* bar height */
static const int tiledraise         = 1;      /* 1 means raise tiled windows when focused */
static const char *fonts[]          = { "FantasqueSansMono Nerd Font:size=16:antialias=true:autohint=true"};

/* Oceanic Next */
static const char col_dark[]        = "#131f26";
static const char col_black[]       = "#1B2B34";
static const char col_gray1[]       = "#343D46";
static const char col_gray2[]       = "#4F5B66";
static const char col_gray3[]       = "#65737E";
static const char col_gray4[]       = "#A7ADBA";
static const char col_lightgray[]   = "#C0C5CE";
static const char col_lightgray1[]  = "#CDD3DE";
static const char col_white[]       = "#D8DEE9";
static const char col_red[]         = "#EC5f67";
static const char col_orange[]      = "#F99157";
static const char col_yellow[]      = "#FAC863";
static const char col_green[]       = "#99C794";
static const char col_cyan[]        = "#5FB3B3";
static const char col_blue[]        = "#6699CC";
static const char col_magenta[]     = "#C594C5";
static const char col_brown[]       = "#AB7967";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] =    { col_gray2,  col_dark,  col_gray1 },
	[SchemeSel]  =    { col_yellow, col_dark,  col_yellow },
	[SchemeTitle]=    { col_yellow,  col_black,  col_red },
	[SchemeLt]   =    { col_yellow, col_dark,  col_cyan },
	[SchemeHid]  =    { col_cyan,   col_gray1,  col_cyan  },
	[SchemeNotify] =  { col_red,    col_white,  col_gray1 },
	[SchemeIndOn]  =  { col_cyan,   col_yellow, col_gray2 },
	[SchemeIndOff] =  { col_green,  col_blue,   col_gray1 },
};


static const char *const autostart[] = {
	"sh", "-c", "/usr/src/dwm/init.sh", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "brave-nightly",NULL,      NULL,       2,            0,           -1 },
	{ "st-256color", NULL,       NULL,       0,            1,           -1 },
	{ "Spotify",     NULL,       NULL,       0,            1,           -1 },
	{ "Discord",     NULL,       NULL,       1 << 4,       1,           -1 },
	{ "Thunar",      NULL,       NULL,       0,            1,           -1 },
	{ "feh",         NULL,       NULL,       0,            1,           -1 },
	{ "Steam",       NULL,       NULL,       0,            1,           -1 },
	{ "Insomnia",    NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",     NULL,       NULL,       2,            0,           -1 },
	{ "Teams",       NULL,       NULL,       3,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "﩯 ",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ " ",      monocle }
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", "-g", "120x30", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ ALTMOD,                       XK_Return, togglefloating, {0} },
	{ ALTMOD|ShiftMask,             XK_Return, togglefullscr,  {0} },
	{ ALTMOD,                       XK_Tab,    focusstack,     {.i = +1 } },
	{ ALTMOD|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_s,      show,           {0} },
	{ MODKEY,                       XK_h,      hide,           {0} },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("st -g 150x40 -e nnn -deU") },
	{ MODKEY,                       XK_i,      spawn,          SHCMD("firefox") },
	{ MODKEY,                       XK_l,      spawn,          SHCMD("brave-bin --force-device-scale-factor=1.25") },
	{ 0,			  XF86XK_AudioLowerVolume, spawn,      SHCMD("pulseaudio-ctl down 5 ; kill -44 $(pidof dwmblocks)") },
	{ 0,			  XF86XK_AudioRaiseVolume, spawn,      SHCMD("pulseaudio-ctl up 5 ; kill -44 $(pidof dwmblocks)") },
	{ 0,			  XF86XK_AudioMute,        spawn,      SHCMD("pulseaudio-ctl mute ; kill -44 $(pidof dwmblocks)") },
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
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

