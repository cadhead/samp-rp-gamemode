#if defined _constants_included
	#endinput
#endif

#define _constants_included

#define SERVER_NAME   "Just another SA:MP Server"
#define MODE_NAME     "SRPGM"
#define VERSION_MAJOR 0
#define VERSION_MINOR 5
#define VERSION_BUILD 3
#define VERSION_EXTRA ""

#define VERSION_STRING "v" #VERSION_MAJOR "." #VERSION_MINOR "." #VERSION_BUILD VERSION_EXTRA
#define GAMEMODE_TEXT  MODE_NAME " " VERSION_STRING

enum (<<= 1)
{
  CMD_ADMIN = 1,
  CMD_MODER
};

new Float:gPosition[3];
new Float:gHealth;
new gRandomValue;
new gString[256], gStringSmall[64], gStringLarge[2048];

#define X     0
#define Y     1
#define Z     2
#define ANGLE 3

stock DIALOG_OK[] = "OK";
stock DIALOG_ACCEPT[] = "Принять";
stock DIALOG_CANCEL[] = "Отмена";
stock DIALOG_CLOSE[] = "Закрыть";
