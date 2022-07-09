#if defined _pl_character_included
  #endinput
#endif

#define _pl_character_included

#include <YSI_Coding\y_hooks>

#define DEFAULT_CHARACTER_POS_X     1715.7280
#define DEFAULT_CHARACTER_POS_Y     -1936.9874
#define DEFAULT_CHARACTER_POS_Z     13.5833
#define DEFAULT_CHARACTER_POS_A     180.0000
#define DEFAULT_CHARACTER_POS_WORLD 0
#define DEFAULT_CHARACTER_POS_INT   0
#define DEFAULT_CHARACTER_SKIN      2

enum e_Player_Character {
  e_cName[MAX_PLAYER_NAME + 1],
  e_cCash,
  e_cSkin,
  Float:e_cSpawnPos[4],
  e_cSpawnInt,
  e_cSpawnWorld,
  e_cDeathStage
}

new gCharacter[MAX_PLAYERS][e_Player_Character];
new gCharacterFormatedName[MAX_PLAYERS][MAX_PLAYER_NAME];

hook OnPlayerConnect(playerid) {
  LoadCharacter(playerid);

  return 1;
}

hook OnPlayerDisconnect(playerid) {
  @__ResetCharacterState(playerid);

  return 1;
}

hook OnPlayerSpawned(playerid) {
  GivePlayerMoney(playerid, gCharacter[playerid][e_cCash]);
  SetPlayerVirtualWorld(playerid, gCharacter[playerid][e_cSpawnWorld]);
  SetPlayerInterior(playerid, gCharacter[playerid][e_cSpawnInt]);

  return 1;
}

stock LoadCharacter(playerid) {
  new
    query[60 + MAX_PLAYER_NAME]
  ;

  GetPlayerName(playerid, gCharacter[playerid][e_cName]);

  mysql_format(
    DB_GetConnectionHandle(),
    query,
    sizeof query,
    "SELECT * FROM `characters` WHERE `Name` = '%e' LIMIT 1",
    gCharacter[playerid][e_cName]
  );

  mysql_tquery(DB_GetConnectionHandle(), query, "@__SetCharacterState", "i", playerid);
}

@__SetCharacterState(playerid);
@__SetCharacterState(playerid) {
  if (cache_num_rows() == 0) {
    KickPlayer(playerid, "Такого персонажа не существует.");

    return 1;
  }

  cache_get_value_int(0, "Cash", gCharacter[playerid][e_cCash]);
  cache_get_value_int(0, "Skin", gCharacter[playerid][e_cSkin]);
  cache_get_value(0, "SpawnPos", gStringSmall);
  sscanf(gStringSmall, "p<|>ffffii", 
    gCharacter[playerid][e_cSpawnPos][X],
    gCharacter[playerid][e_cSpawnPos][Y],
    gCharacter[playerid][e_cSpawnPos][Z],
    gCharacter[playerid][e_cSpawnPos][ANGLE],
    gCharacter[playerid][e_cSpawnWorld],
    gCharacter[playerid][e_cSpawnInt]
  );

  SetSpawnPointDefault(playerid);
  
  SetSpawnInfo(
    playerid,
    0,
    gCharacter[playerid][e_cSkin],
    XYZ0(gCharacter[playerid][e_cSpawnPos]),
    gCharacter[playerid][e_cSpawnPos][ANGLE],
    0, 0, 0, 0, 0, 0
  );

  FormatCharacterName(playerid);

  SpawnPlayer(playerid);

  return 1;
}

@__ResetCharacterState(playerid);
@__ResetCharacterState(playerid) {
  MemSet(gCharacter[playerid], 0);
}

static SetSpawnPointDefault(playerid) {
  for (new i; i < 3; i++) { // Check is character has no spawn point
    if (gCharacter[playerid][e_cSpawnPos][i] == 0) break;
    else return;
  }

  gCharacter[playerid][e_cSpawnPos][X] 		 = DEFAULT_CHARACTER_POS_X;
  gCharacter[playerid][e_cSpawnPos][Y]     = DEFAULT_CHARACTER_POS_Y;
  gCharacter[playerid][e_cSpawnPos][Z]     = DEFAULT_CHARACTER_POS_Z;
  gCharacter[playerid][e_cSpawnPos][ANGLE] = DEFAULT_CHARACTER_POS_A;
}

static FormatCharacterName(playerid) {
  new name[MAX_PLAYER_NAME + 1];

  GetPlayerName(playerid, name);

  for (new i = 0; i < MAX_PLAYER_NAME; i++) {
    if (name[i] == '_') name[i] = ' ';
  }

  strcopy(gCharacterFormatedName[playerid], name);
}

stock GetCharacterNameByID(dbid) {
	new query[120], returnString[60];
	
	mysql_format(DB_GetConnectionHandle(), query, sizeof(query), "SELECT Name FROM characters WHERE ID = %i", dbid);
	new Cache:cache = mysql_query(DB_GetConnectionHandle(), query);
	
	if(!cache_num_rows())
		returnString = "None";
		
	else
		cache_get_value(0, "Name", returnString);
	
	cache_delete(cache);
	return returnString;
}
