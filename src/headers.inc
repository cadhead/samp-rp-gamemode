#if defined _headers_included
	#endinput
#endif

#define _headers_included

// General
forward OnGameModeUpdate();
forward OnPlayerSpawned(playerid);

// DB
forward DB_Connect(const host[], const user[], const pass[], const db[]);
forward DB_ConnectionClose();
forward MySQL:DB_GetConnectionHandle();
forward DB_OnGameModeInit();
forward DB_OnGameModeExit();

// Player
forward Player_OnPlayerConnect(playerid);
forward Player_OnPlayerDisconnect(playerid);

// Characters
forward Character_OnPlayerSpawned(playerid);

// Chat
forward Chat_OnPlayerText(playerid, text[]);
forward Chat_OnGameModeUpdate();

// Vehicle
forward Vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
