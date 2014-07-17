#ifndef ___GLOBALS_H___
#define ___GLOBALS_H___

//------------------------------------------------------------------- directory

#define CONFIG_DIR "/adm/etc/"
#define DATA_DIR   "/data/"
#define LOG_DIR    "/log/"

//--------------------------------------------- non-inheritable standard object

#define LOGIN_OB "/obj/login"
#define USER_OB  "/obj/user"

//------------------------------------------------- inheritable standard object

#define CHARACTER "/std/character"

//---------------------------------------------------------------------- daemon

#define CHANNEL_D  "/adm/daemons/channel"
#define COMMAND_D  "/adm/daemons/command"
#define LOGIN_D    "/adm/daemons/login"
#define SECURITY_D "/adm/daemons/security"

//--------------------------------------------------------------------- feature

#define F_DBASE "/feature/dbase"
#define F_SAVE  "/feature/save"

//--------------------------------------------------------------------- user ID

#define BACKBONE_UID "BACKBONE"
#define SYSTEM_UID   "SYSTEM"
#define ROOT_UID     "ROOT"

//-------------------------------------------------------------------- function

#define FP_OWNER_DESTED 0x20

//------------------------------------------------------------------- localtime

#define LT_SEC    0
#define LT_MIN    1
#define LT_HOUR   2
#define LT_MDAY   3
#define LT_MON    4
#define LT_YEAR   5
#define LT_WDAY   6
#define LT_YDAY   7
#define LT_GMTOFF 8
#define LT_ZONE   9

//------------------------------------------------------------ ANSI escape code

#define ESC   ""
#define NOR   ESC"[0m"
#define U     ESC"[4m"
#define BLINK ESC"[5m"
#define REV   ESC"[7m"

//------------------------------------------------------------ foreground color

#define BLK ESC"[22;30m"
#define RED ESC"[22;31m"
#define GRN ESC"[22;32m"
#define YEL ESC"[22;33m"
#define BLU ESC"[22;34m"
#define MAG ESC"[22;35m"
#define CYN ESC"[22;36m"
#define WHT ESC"[22;37m"

//--------------------------------------------- high intensity foreground color

#define GRAY ESC"[1;30m"
#define HIR  ESC"[1;31m"
#define HIG  ESC"[1;32m"
#define HIY  ESC"[1;33m"
#define HIB  ESC"[1;34m"
#define HIM  ESC"[1;35m"
#define HIC  ESC"[1;36m"
#define HIW  ESC"[1;37m"

//------------------------------------------------------------ background color

#define BBLK ESC"[40m"
#define BRED ESC"[41m"
#define BGRN ESC"[42m"
#define BYEL ESC"[43m"
#define BBLU ESC"[44m"
#define BMAG ESC"[45m"
#define BCYN ESC"[46m"
#define BWHT ESC"[47m"

//--------------------------------------------------------------- miscellaneous

#define NULL                  undefined_value()
#define read_config(filename) strip(split(read_file(filename),"\n"),'#')

//-----------------------------------------------------------------------------

#endif
