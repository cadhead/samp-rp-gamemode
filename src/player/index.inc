#if defined _pl_index_included
	#endinput
#endif

#define _pl_index_included

#include <YSI_Coding\y_hooks>

#include "./player/kick"
#include "./player/character"
#include "./player/death"
#include "./player/anim"
#include "./player/walkstyle"

hook OnPlayerConnect(playerid) {
  TogglePlayerSpectating(playerid, true);
  SetPlayerColor(playerid, 0xFFFFFF00);

  return 1;
}

hook OnPlayerSpawned(playerid) {
  TogglePlayerSpectating(playerid, false);

  return 1;
}
