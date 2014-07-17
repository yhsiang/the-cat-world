#ifndef ___GLOBALS_H___
#define ___GLOBALS_H___

//------------------------------------------------------------------- directory

#define CONFIG_DIR "/adm/etc/"
#define DATA_DIR   "/data/"

//--------------------------------------------- non-inheritable standard object

#define LOGIN_OB "/obj/login"
#define USER_OB  "/obj/user"

//------------------------------------------------- inheritable standard object

#define CHARACTER "/std/character"

//--------------------------------------------------------------------- feature

#define F_DBASE "/feature/dbase"
#define F_SAVE  "/feature/save"

//--------------------------------------------------------------------- user ID

#define BACKBONE_UID "BACKBONE"
#define SYSTEM_UID   "SYSTEM"
#define ROOT_UID     "ROOT"

//-------------------------------------------------------------------- function

#define FP_OWNER_DESTED 0x20

//--------------------------------------------------------------- miscellaneous

#define NULL                  undefined_value()
#define read_config(filename) strip(split(read_file(filename),"\n"),'#')

//-----------------------------------------------------------------------------

#endif
