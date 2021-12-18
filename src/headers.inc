#if defined _headers_included
	#endinput
#endif

#define _headers_included

// General
forward OnGameModeUpdate();
forward OnWorldSave();

// DB
forward DB_Connect(const host[], const user[], const pass[], const db[]);
forward DB_ConnectionClose();
forward MySQL:DB_GetConnectionHandle();

// Player
forward OnPlayerSpawned(playerid);

// Other
forward OnEnterStart(playerid, enteridx);
forward OnExitStart(playerid, enteridx);
forward OnEnterDone(playerid, enteridx);
forward OnExitDone(playerid, enteridx);