/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
    "monospace:size=10"
};
static const char dmenufont[]       = "monospace:size=10";
static const char normbordercolor[] = "#0099FF";
static const char normbgcolor[]     = "#002b36";
static const char normfgcolor[]     = "#839496";
static const char selbordercolor[]  = "#0099FF";
static const char selbgcolor[]      = "#586e75";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 1;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "view", "work", "doc", "four", "five", "thunar", "steam", "web", "music", "system" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
    /* first entry is default */
	{ "[@]",      spiral },
	{ "[T]",      tile },
    /* no layout function means floating behavior */
	{ "[F]",      NULL },
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *xlockcmd[] = { "slimlock", NULL };
static const char *thunarcmd[] = { "thunar", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = xlockcmd} },
    { MODKEY|ShiftMask|ControlMask, XK_Return, spawn,          {.v = thunarcmd} },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    //{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    //{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_s,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[0]} },
    //{ MODKEY,                       XK_space,  setlayout,      {0} },
    //{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    //{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    //{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    //{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    //{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    TAGKEYS(                        XK_0,                     9)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

