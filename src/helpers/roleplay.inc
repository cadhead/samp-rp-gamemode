#if defined _hlp_roleplay_included
	#endinput
#endif

#define _hlp_roleplay_included

stock GetRoleplayName(playerid, const result[]) {
  GetPlayerName(playerid, result);

  for (new i = 0; i < MAX_PLAYER_NAME; i++) {
    if (result[i] == '_') result[i] = ' ';
  }
}
