#if defined _pl_index_included
	#endinput
#endif

#define _pl_index_included

#include "./player/kick"
#include "./player/character"
#include "./player/death"
#include "./player/anim"
#include "./player/walkstyle"

#include <YSI_Coding\y_hooks>
hook OnPlayerConnect(playerid) {
  TogglePlayerSpectating(playerid, true);
  SetPlayerColor(playerid, 0xFFFFFF00);

  return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerSpawned(playerid) {
  TogglePlayerSpectating(playerid, false);

  return 1;
}
