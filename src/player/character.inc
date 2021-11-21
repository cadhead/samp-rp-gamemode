#if defined _pl_character_included
	#endinput
#endif

#define _pl_character_included

#define DEFAULT_CHARACTER_POS_X     1715.7280
#define DEFAULT_CHARACTER_POS_Y     -1936.9874
#define DEFAULT_CHARACTER_POS_Z     13.5833
#define DEFAULT_CHARACTER_POS_WORLD 0
#define DEFAULT_CHARACTER_POS_INT   0
#define DEFAULT_CHARACTER_CASH      500
#define DEFAULT_CHARACTER_SKIN      2

enum e_Player_Character {
	e_cName[MAX_PLAYER_NAME + 1],
	e_cCash,
	e_cSkin,
	Float:e_cSpawnX,
	Float:e_cSpawnY,
	Float:e_cSpawnZ,
	e_cSpawnInt,
	e_cSpawnWorld
}

new gCharacter[MAX_PLAYERS][e_Player_Character];
new gCharacterFormatedName[MAX_PLAYERS][MAX_PLAYER_NAME];

hook OnPlayerSpawned(playerid) {
  GivePlayerMoney(playerid, gCharacter[playerid][e_cCash]);
  SetPlayerVirtualWorld(playerid, gCharacter[playerid][e_cSpawnWorld]);
  SetPlayerInterior(playerid, gCharacter[playerid][e_cSpawnInt]);

  TogglePlayerSpectating(playerid, false);

  return 1;
}

stock Character_LoadData(playerid) {
	new
		query[60 + MAX_PLAYER_NAME]
	;

	GetPlayerName(playerid, gCharacter[playerid][e_cName]);

	mysql_format(
		DB_GetConnectionHandle(),
		query,
		sizeof query,
		"SELECT * FROM `characters` WHERE `name` = '%e' LIMIT 1",
		gCharacter[playerid][e_cName]
	);

	mysql_tquery(DB_GetConnectionHandle(), query, "Character_SetData", "i", playerid);
}

forward Character_SetData(playerid);
public Character_SetData(playerid) {
	if (cache_num_rows() == 0) {
		KickPlayer(playerid, "Такого персонажа не существует.");

		return 1;
	}

	cache_get_value_int(0, "cash", gCharacter[playerid][e_cCash]);
	cache_get_value_int(0, "skin", gCharacter[playerid][e_cSkin]);

	cache_get_value_float(0, "spawnX", gCharacter[playerid][e_cSpawnX]);
	cache_get_value_float(0, "spawnY", gCharacter[playerid][e_cSpawnY]);
	cache_get_value_float(0, "spawnZ", gCharacter[playerid][e_cSpawnZ]);
	cache_get_value_int(0, "spawnInt", gCharacter[playerid][e_cSpawnInt]);
	cache_get_value_int(0, "spawnWorld", gCharacter[playerid][e_cSpawnWorld]);

	

	SetSpawnInfo(
		playerid,
		0,
		gCharacter[playerid][e_cSkin],
		gCharacter[playerid][e_cSpawnX],
		gCharacter[playerid][e_cSpawnY],
		gCharacter[playerid][e_cSpawnZ],
		180.0, 0, 0, 0, 0, 0, 0
	);

	FormatCharacterName(playerid);

	SpawnPlayer(playerid);

	return 1;
}

stock Character_ResetData(playerid) {
	memset(gCharacter[playerid], 0);
}

static FormatCharacterName(playerid) {
  new name[MAX_PLAYER_NAME + 1];

  GetPlayerName(playerid, name);

  for (new i = 0; i < MAX_PLAYER_NAME; i++) {
    if (name[i] == '_') name[i] = ' ';
  }

  strcopy(gCharacterFormatedName[playerid], name);
}

