//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {

        /*Icon*/        /*Command*/             /*Update Interval*/     /*Update Signal*/
        {"",            "mpd.sh",                   2,                      1},

        {"",            "network.sh",               3,                      0},

        {"",            "temperature.sh",           10,                     1},

        {"",            "~/.config/dwmblocks/scripts/brightness.sh",            2,                      1},

        {"",            "volume.sh",                2,                      1},

        {"",            "battery.sh",               5,                      1},

//        {" ",       "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",      30,             0},

        {" ",          "date '+%a %d %b %R' ",     5,                      0},

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "  ";
static unsigned int delimLen = 5;
