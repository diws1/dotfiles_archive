/* See LICENSE file for copyright and license details. */

/* multimediakey */
#include <X11/XF86keysym.h>

static const char *up_vol[]   = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "1%+", NULL };
static const char *down_vol[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "1%-", NULL };
static const char *mute_vol[] = { "wpctl", "set-mute",   "@DEFAULT_AUDIO_SINK@", "toggle", NULL };

static const char *bright_up[]     = { "brightnessctl", "set", "+5%", NULL };
static const char *bright_down[]   = { "brightnessctl", "set", "5%-", NULL };

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 1;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 18;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Terminus (TTF):size=9", "FontAwesome:size=8", "Liberation Mono:size=12" };
//static const char dmenufont[]       = "monospace:size=10";
static unsigned int baralpha        = 229;
static unsigned int borderalpha     = OPAQUE;
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";

static const char col_bg[]          = "#1B1B1B";
static const char col_fg[]          = "#F0F0F0";
static const char col_bgsel[]       = "#161616";
static const char col_fgsel[]       = "#98971A";
//static const char col_bfocus[]      = "#C5C8C6";
static const char col_bfocus[]      = "#4E3A75";
static const char col_bnormal[]     = "#282A2E";

static const char *colors[][3]      = {
        /*                      fg         bg          border   */
        [SchemeNorm] =   { col_fg,    col_bg,     col_bnormal },
        [SchemeSel]  =   { col_fgsel, col_bgsel,  col_bfocus },
        [SchemeWarn] =   { col_black, col_yellow, col_red },
        [SchemeUrgent]=  { col_white, col_red,    col_red },
                         { "#1b1b1b", "#282a2e",  "#282a2e" },
                         { "#cc6666", "#1b1b1b",  "#282a2e" },
                         { "#b5bd68", "#1b1b1b",  "#282a2e" },
                         { "#de935f", "#1b1b1b",  "#282a2e" },
                         { "#f0c674", "#1b1b1b",  "#282a2e" },
                         { "#81a2be", "#1b1b1b",  "#282a2e" },
                         { "#b294bb", "#1b1b1b",  "#282a2e" },
                         { "#8abeb7", "#1b1b1b",  "#282a2e" },
};

static const char *const autostart[] = {
        "nitrogen", "--restore", "&", NULL,
        "dwmblocks", "&", NULL,
        //"xwallpaper", "--clear", "--zoom", "Wallpapers/monokai-japan.png", "&", NULL,
        "killall", "xmobar", NULL,
        "/usr/lib/x86_64-linux-gnu/xfce4/notifyd/xfce4-notifyd", "&", NULL,
        //"st", NULL,
        NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "▫", "▫", "▫", "▫", "▫", "▫", "▫", "▫", "▫" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            1,           -1 },
        { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
//static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *terminal[]   = { "urxvt", NULL };
static const char *file[]       = { "thunar", NULL };
static const char *menu[]       = { "rofi", "-show", "drun", NULL };
static const char *browser[]    = { "brave-browser", NULL };
static const char *music[]      = { "urxvt", "-e", "ncmpcpp", NULL };
static const char *screenshot[] = { "xfce4-screenshooter", NULL };
static const char *scrot[]      = { "scrot", "Pictures/Screenshots/scrot_%a-%d%b%y_%R.png", NULL };
static const char *lock[]       = { "xtrlock", NULL };
static const char *notif1[]     = { "notify-send", "Volume Mute", NULL };
static const char *notif2[]     = { "notify-send", "Volume Down", NULL };
static const char *notif3[]     = { "notify-send", "Volume Up", NULL };
static const char *notif4[]     = { "notify-send", "Brightness Down", NULL };
static const char *notif5[]     = { "notify-send", "Brightness Up", NULL };

static const Key keys[] = {
        /* modifier                     key        function        argument */
        { 0,             XF86XK_AudioMute,         spawn,          {.v = mute_vol } },
        { 0,             XF86XK_AudioLowerVolume,  spawn,          {.v = down_vol } },
        { 0,             XF86XK_AudioRaiseVolume,  spawn,          {.v = up_vol } },
        { 0,             XF86XK_AudioMute,         spawn,          {.v = notif1 } },
        { 0,             XF86XK_AudioLowerVolume,  spawn,          {.v = notif2 } },
        { 0,             XF86XK_AudioRaiseVolume,  spawn,          {.v = notif3 } },

        { 0,             XF86XK_MonBrightnessDown, spawn,          {.v = bright_down } },
        //{ 0,           XF86XK_MonBrightnessUp,   spawn,          {.v = bright_up } },
        { MODKEY,                       XK_F5,     spawn,          {.v = bright_up } },
        { 0,             XF86XK_MonBrightnessDown, spawn,          {.v = notif4 } },
        { MODKEY,                       XK_F5,     spawn,          {.v = notif5 } },

        { MODKEY,                       XK_a,      spawn,          {.v = terminal } },
        { MODKEY,                       XK_d,      spawn,          {.v = file } },
        { MODKEY,                       XK_space,  spawn,          {.v = menu } },
        { MODKEY,                       XK_b,      spawn,          {.v = browser } },
        { MODKEY,                       XK_m,      spawn,          {.v = music } },
        { MODKEY,                       XK_s,      spawn,          {.v = screenshot } },
        { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = scrot } },
        { MODKEY,                       XK_Delete, spawn,          {.v = lock } },
        { MODKEY,                       XK_f,      togglebar,      {0} },
        { MODKEY,                       XK_x,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_c,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_v,      incnmaster,     {.i = +1 } },
        { MODKEY|ShiftMask,             XK_v,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_n,      setlayout,      {.v = &layouts[1]} },
        { MODKEY|ShiftMask,             XK_n,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_z,      setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
        { MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
        { MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
        { MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
        { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
        { MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
        { MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
        { MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
        { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
        { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
        { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
        { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
        { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
        { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
        { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
        { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
        { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
        { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY,                       XK_Escape, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
        /* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button2,        spawn,          {.v = terminal } },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
