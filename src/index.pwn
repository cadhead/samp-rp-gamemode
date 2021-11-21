#pragma tabsize 2

#include <a_samp>
#include <a_mysql>
#include <sscanf2>
#include <YSI_Coding\y_hooks>
#include <streamer>
#include <Pawn.CMD>
#include <foreach>
#include <formatex>
#include <mdialog>
#define ZMSG_MAX_CHAT_LENGTH 84
#define ZMSG_MAX_PLAYER_CHAT_LENGTH 84
#define ZMSG_SEPARATORS_LIST ' '
#define ZMSG_HYPHEN_END   " ..."
#define ZMSG_HYPHEN_START "... "
#include <zmessage>
#include <weapon-config>

#include "./colors"
#include "./constants"
#include "./headers"
#include "./helpers/index"

#include "./db/index"
#include "./player/index"
#include "./chat/index"
#include "./vehicle/index"
#include "./admin/index"

main() {}

public OnGameModeInit() {
  ShowNameTags(true);
  AllowInteriorWeapons(true);
  EnableStuntBonusForAll(false);
  ShowPlayerMarkers(false);
  ManualVehicleEngineAndLights();
  EnableVehicleFriendlyFire();
  SetVehiclePassengerDamage(true);
  SetDisableSyncBugs(true);

  SetTimer("OnGameModeUpdate", 500, true);

  AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);

  return 1;
}

public OnGameModeUpdate() {

  return 1;
}

public OnGameModeExit() {

  return 1;
}

public OnPlayerConnect(playerid) {

  return 1;
}

public OnPlayerDisconnect(playerid, reason) {

  return 1;
}

public OnPlayerSpawn(playerid) {
  SetTimerEx("OnPlayerSpawned", 1000, 0, "d", playerid);

  return 1;
}


public OnPlayerRequestClass(playerid, classid) {
  return 0;
}

public OnPlayerSpawned(playerid) {
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

public OnVehicleSpawn(vehicleid) {

  return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

  return 1;
}

public OnRconCommand(cmd[]) {
	return 0;
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
