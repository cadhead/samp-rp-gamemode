#if defined _enters_included
  #endinput
#endif

#define _enters_included

#include <YSI_Coding\y_hooks>

#define MAX_ENTERS 256

enum e_Enters {
  e_ID,
  e_Name[32],
  e_Desc[144],
  e_CreatedBy,
  Float:e_PosEnter[3],
  e_PosEnterWorld,
  e_PosEnterInt,
  Float:e_PosExit[3],
  e_PosExitWorld,
  e_PosExitInt,
  e_WantSave
}

new gEnter[MAX_ENTERS][e_Enters];
new static count = 0;

hook OnGameModeInit() {
  LoadEnters();

  return 1;
}

hook OnGameModeExit() {
  SaveEnters();

  return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
  switch (newkeys) {
    case KEY_YES: {
      callcmd::enter(playerid);
      callcmd::exit(playerid);
    }
  }

  return 1;
}

static LoadEnters() {
  mysql_tquery(DB_GetConnectionHandle(), "SELECT * FROM `enters`", "@__SetEntersState");
}

@__SetEntersState();
@__SetEntersState() {
  new row_count;

  cache_get_row_count(row_count);

  for (new i; i < row_count; i++) {
    cache_get_value_int(i, "ID", gEnter[i][e_ID]);
    cache_get_value(i, "Name", gEnter[i][e_Name]);
    cache_get_value(i, "Description", gEnter[i][e_Desc]);
    cache_get_value(i, "EnterPos", gString);
    sscanf(gString, "p<|>fffii", 
      XYZ0(gEnter[i][e_PosEnter]),
      gEnter[i][e_PosEnterWorld],
      gEnter[i][e_PosEnterInt]
    );
    cache_get_value(i, "ExitPos", gString);
    sscanf(gString, "p<|>fffii", 
      XYZ0(gEnter[i][e_PosExit]),
      gEnter[i][e_PosExitWorld],
      gEnter[i][e_PosExitInt]
    );
    cache_get_value_int(i, "CreatedBy", gEnter[i][e_CreatedBy]);

    count++;
    CreateEnter3DText(i);
  } 
}

static SaveEnters() {
  static const 
    queryStr[] = "UPDATE `enters`\
    SET `Name` = '%e',\
    `Description` = '%e'\
    WHERE `ID` = '%d'"
  ; // 92

  new query[92 + 32 + 144 + 11];

  for (new i; i < count; i++) {
    if (!gEnter[i][e_WantSave]) continue;

    gEnter[i][e_WantSave] = 0;

    mysql_format(DB_GetConnectionHandle(),
      query, sizeof query,
      queryStr,
      gEnter[i][e_Name],
      gEnter[i][e_Desc],
      gEnter[i][e_ID]
    );

    mysql_tquery(DB_GetConnectionHandle(), query);
  }
}

EntersAddOne(const pos_enter[], const pos_exit[], const name[], const desc[] = "", accountid = -1) {
  static const 
    queryStr[] = "INSERT INTO `enters`\
    (`EnterPos`, `ExitPos`, `Name`, `Description`, `CreatedBy`)\
    VALUES ('%e', '%e', '%e', '%e', '%d')"
  ; // 128

  new query[128 + 64 + 64 + 32 + 144];

  mysql_format(DB_GetConnectionHandle(), query, sizeof query, queryStr, pos_enter, pos_exit, name, desc, accountid);
  mysql_query(DB_GetConnectionHandle(), query);

  gEnter[count][e_ID] = cache_insert_id();
  gEnter[count][e_CreatedBy] = accountid;
  sscanf(pos_enter, "p<|>fffii", 
    XYZ0(gEnter[count][e_PosEnter]),
    gEnter[count][e_PosEnterWorld],
    gEnter[count][e_PosEnterInt]
  );

  sscanf(pos_exit, "p<|>fffii", 
    XYZ0(gEnter[count][e_PosExit]),
    gEnter[count][e_PosExitWorld],
    gEnter[count][e_PosExitInt]
  );

  strcopy(gEnter[count][e_Name], name);
  strcopy(gEnter[count][e_Desc], desc);

  CreateEnter3DText(count);

  count++;
}

EntersDeleteOne(id) {

}

hook function SetPlayerPos(playerid, Float:x, Float:y, Float:z) {
  new
    items[1],
    streamer_count = Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_OBJECT, items, sizeof(items), 300.0),
    freeze_time = (GetPlayerPing(playerid) * 4) + (streamer_count * 2) + 1550
  ;

  Streamer_UpdateEx(playerid, x, y, z, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

  if (!GetPVarInt(playerid, "IsFrozen") && streamer_count) {
    TogglePlayerControllable(playerid, 0);
    SetTimerEx(!"@__UnFreezePlayer", freeze_time, false, !"d", playerid);
    SetPVarInt(playerid, "IsFrozen", 1);
  }

  continue(playerid, x, y, z + 0.3);
}

CMD:enter(playerid) {
  for (new i; i < count; i++) {
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, XYZ0(gEnter[i][e_PosEnter]))) continue;
    if (gEnter[i][e_PosEnterWorld] != GetPlayerVirtualWorld(playerid)) continue;
    if (gEnter[i][e_PosEnterInt] != GetPlayerInterior(playerid)) continue;

    SetPlayerPos(playerid, XYZ0(gEnter[i][e_PosExit]));
    SetPlayerVirtualWorld(playerid, gEnter[i][e_PosExitWorld]);
    SetPlayerInterior(playerid, gEnter[i][e_PosExitInt]);
    if (!isnull(gEnter[i][e_Desc])) {
      SendClientMessage(playerid, COLOR_ACTIONS, "* %s", false, gEnter[i][e_Desc]);
    }

    return 1;
  }

  return 1;
}

CMD:exit(playerid) {
  for (new i; i < count; i++) {
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, XYZ0(gEnter[i][e_PosExit]))) continue;
    if (gEnter[i][e_PosExitWorld] != GetPlayerVirtualWorld(playerid)) continue;
    if (gEnter[i][e_PosExitInt] != GetPlayerInterior(playerid)) continue;

    SetPlayerPos(playerid, XYZ0(gEnter[i][e_PosEnter]));
    SetPlayerVirtualWorld(playerid, gEnter[i][e_PosEnterWorld]);
    SetPlayerInterior(playerid, gEnter[i][e_PosEnterInt]);

    return 1;
  }

  return 1;
}

static CreateEnter3DText(enterid) {
  gString[0] = EOS;
  format( gString, sizeof gString,cWHITE"%s\n"cBLUE"[Press Y]", gEnter[enterid][e_Name], gEnter[enterid][e_ID]);
  CreateDynamic3DTextLabel(
    gString,
    COLOR_BLUE,
    XYZ0(gEnter[enterid][e_PosEnter]), 4.0, 
    INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
    gEnter[enterid][e_PosEnterWorld], gEnter[enterid][e_PosEnterInt]
  );
}

@__UnFreezePlayer(playerid);
@__UnFreezePlayer(playerid) {
  SetPVarInt(playerid, "IsFrozen", 0);
  TogglePlayerControllable(playerid, 1);
}
