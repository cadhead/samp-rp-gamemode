#if defined _pl_index_included
	#endinput
#endif

#define _pl_index_included

#include "./player/kick"
#include "./player/character"
#include "./player/death"

public Player_OnPlayerConnect(playerid) {
  TogglePlayerSpectating(playerid, true);
  SetPlayerColor(playerid, 0xFFFFFF00);

  Character_LoadData(playerid);

  return 1;
}

public Player_OnPlayerDisconnect(playerid) {
  Character_ResetData(playerid);

  return 1;
}
