#pragma tabsize 2
#pragma warning disable 203

#include <a_samp>
#define FIXES_ExplicitOptions 0
#define FIXES_Single 1
#define FIXES_DefaultDisabled 1
#define FIX_GetPlayerWeather 1 
#define FIX_GetWeather 1 
#define FIX_GetWorldTime 1
#define FIX_API 1
#define FIX_strfind 1
#define FIX_strcmp 1
#define FIX_SetPlayerColor 1
#define FIX_OnPlayerSpawn	1
#define FIX_ClearAnimations 1
#define FIX_random 1
#define FIX_Kick 1
#define FIX_TrainExit 1
#define FIX_strins 1
#define FIX_SetPlayerSkin	1
#define FIX_SetSpawnInfo 1
#define FIX_const 1
#include <fixes>
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_MODE_CACHE
#define YSI_NO_OPTIMISATION_MESSAGE
#include <YSI_Coding\y_hooks>
#include <a_mysql>
#include <sscanf2>
#include <streamer>
#include <foreach>
#include <formatex>
#include <mdialog>
#include <pawn.CMD>
#define ZMSG_MAX_CHAT_LENGTH 84
#define ZMSG_MAX_PLAYER_CHAT_LENGTH 84
#define ZMSG_SEPARATORS_LIST ' '
#define ZMSG_HYPHEN_END   " ..."
#define ZMSG_HYPHEN_START "... "
#include <zmessage>
#include <weapon-config>
#include <realtime-clock>

#include "./colors"
#include "./constants"
#include "./headers"
#include "./helpers/index"

#include "./db/index"
#include "./player/index"
#include "./chat/index"
#include "./vehicle/index"
#include "./enters"
#include "./properties/index"
#include "./admin/index"

main() {}

public OnGameModeInit() {
  SetGameModeText(GAMEMODE_TEXT);
  SendRconCommand("hostname "SERVER_NAME);

  ShowNameTags(true);
  AllowInteriorWeapons(true);
  DisableInteriorEnterExits();
  EnableStuntBonusForAll(false);
  ShowPlayerMarkers(false);
  ManualVehicleEngineAndLights();
  EnableVehicleFriendlyFire();
  SetVehiclePassengerDamage(true);
  SetDisableSyncBugs(true);

  new save_world_timing = DURATION(1 hour);

  SetTimer("OnGameModeUpdate", 500, true);
  SetTimer("OnWorldSave", save_world_timing, true);

  RealTime_SetInterval(10000, false);
  RealTime_Sync();

  AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);

  return 1;
}

public OnGameModeUpdate() {

  return 1;
}

public OnGameModeExit() {
  DB_ConnectionClose();
  RealTime_StopTime();

  return 1;
}

public OnWorldSave() {
  return 1;
}

public OnWorldTimeUpdate(hour, minute) {
  SetWorldTime(hour);

  return 1;
}

public OnPlayerConnect(playerid) {
  SetPlayerTime(playerid, RealTime_GetHour(), RealTime_GetMinute());

  return 1;
}

public OnPlayerDisconnect(playerid, reason) {

  return 1;
}

public OnPlayerSpawn(playerid) {
  SetTimerEx("OnPlayerSpawned", 1000, 0, "d", playerid);

  return 1;
}

public OnPlayerSpawned(playerid) {
  return 1;
}

public OnPlayerRequestClass(playerid, classid) {
  return 0;
}

public OnPlayerDeath(playerid, killerid, reason) {
  return 1;
}

public OnPlayerDeathFinished(playerid, bool:cancelable) {
  return 1;
}

public OnPlayerDamage(&playerid, &Float:amount, &issuerid, &weapon, &bodypart) {
  return 1;
}

public OnPlayerDamageDone(playerid, Float:amount, issuerid, weapon, bodypart) {
  return 1;
}

public OnPlayerText(playerid, text[]) {

  return 0;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags) {
  return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
  if (result == -1) {
    SendClientMessage(playerid, COLOR_WHITE, "> Команды не существует.", 0);

    return 0;
  }

  return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

  return 1;
}

public OnVehicleSpawn(vehicleid) {

  return 1;
}

public OnRconCommand(cmd[]) {
	return 0;
}

public OnPlayerPickUpDynamicPickup(playerid, STREAMER_TAG_PICKUP:pickupid) {
  new enteridx = IsPlayerNearAnyEnter(playerid);
  new propidx = GetPropertyByEnterid(gEnter[enteridx][e_enID]);

  if (enteridx == -1) return;
  OnEnterPickupPickUp(playerid, pickupid, enteridx, propidx);
}


// stock CreatePlayerPassword(playerid, password[]) {
//     new letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
//     new length = strlen(letters);
//     for (new i = 0; i <= 64; i++) {
//         Player[playerid][pSalt][i] =
//             letters[random(length)];
//     }

//     SHA256_PassHash(password, Player[playerid][pSalt],
//         Player[playerid][pPass], 65);

//     return 1;
// } 
