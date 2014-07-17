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

#define COMMAND_D "/adm/daemons/command"
#define LOGIN_D   "/adm/daemons/login"

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

//--------------------------------------------------------------- miscellaneous

#define NULL                  undefined_value()
#define read_config(filename) strip(split(read_file(filename),"\n"),'#')

//-----------------------------------------------------------------------------

#endif
