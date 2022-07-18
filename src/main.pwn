#pragma tabsize 2
#pragma warning disable 203

#include <a_samp>
#include <a_http>

#undef MAX_PLAYERS
#define MAX_PLAYERS                     (100)
#undef MAX_VEHICLES
#define MAX_VEHICLES                    (1000)

#define GMT_ZONE_DIFFERENCE             (0)
#define SERVER_UNLOCK_TIME              (1)

// Fixes.inc
#define FIXES_GetMaxPlayersMsg  0
#define FIXES_ServerVarMsg      0
#define FIX_OnDialogResponse    0
#define FIX_GetPlayerDialog	    0
#define	MAX_IP_CONNECTS         3
#define FIX_file_inc            0
#define FIX_const
#include <fixes>

#include <sscanf2>

#include <callbacks>

#include <map-zones>

#include <chrono>

// Streamer
#include <streamer>
#define OBJECT_STREAM_LIMIT (700)


// YSI
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_MODE_CACHE
#define YSI_NO_OPTIMISATION_MESSAGE
#define CGEN_MEMORY	  (90000)
#define MAX_COMMANDS  (1024)
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_inline>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_va>
#include <YSI_Data\y_iterate>
#include <YSI_Server\y_flooding>
#include <YSI_Game\y_vehicledata>

#include <Pawn.CMD>

#include <a_mysql>
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Extra\y_inline_timers>

#include "revision.inc"
#include <mdialog>

#define SERVER_NAME     "Just Another RP server"
#define HOSTNAME        #SERVER_NAME" [0.3.7]"
#define WEB_URL	        "https://just-another-rp-server.com/"
#define GAMEMODE_NAME   "JA/RPGM"
#define SCRIPT_VERSION  #GAMEMODE_NAME" v0.0.0.-"#GIT_REV

// Modules
#include <Preincludes>
#include <Server>
#include <Systems>
#include <Admin>
#include <Player>
// #include <Character>

main() {}

public OnPlayerText(playerid, text[]) {
  return 0;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags) {
  if (!IsPlayerLoggedIn(playerid)) return 0;
  if ((flags & CMD_OWNER)) return 0;
  if ((flags & CMD_ADMIN)) return 0;
  if ((flags & CMD_MODER)) return 0;
  if ((flags & CMD_HELPER)) return 0;
  if ((flags & CMD_PREMIUM)) return 0;
  if ((flags & CMD_USER)) return 0;

  return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
  if (result == -1) {
    SendClientMessage(playerid, COLOR_WHITE, "> Команды не существует.");

    return 0;
  }

  return 1;
}
