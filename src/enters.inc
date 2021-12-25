#if defined _enters_included
  #endinput
#endif

#define _enters_included

#include <YSI_Coding\y_hooks>

#define MAX_ENTERS 1024

#define ENTER_TYPE_WHNOKNOWS 0
#define ENTER_TYPE_PROPERTY  1

enum e_Enters {
  e_enID,
  e_enName[64],
  e_enDesc[144],
  e_enType,
  Float:e_enPosEnter[3],
  e_enPosEnterWorld,
  e_enPosEnterInt,
  Float:e_enPosExit[3],
  e_enPosExitWorld,
  e_enPosExitInt,
  STREAMER_TAG_3D_TEXT_LABEL:e_enText3D
}

new gEnter[MAX_ENTERS][e_Enters];
new bool:gEntersIsLoaded;

static count = 0;
static bool:want_save[MAX_ENTERS];

#define GetEnterID(%0)   gEnter[%0][e_enID]
#define GetEnterName(%0) gEnter[%0][e_enName]
#define GetEnterDesc(%0) gEnter[%0][e_enDesc]

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

public OnEnterStart(playerid, enteridx) { return 1; }
public OnExitStart(playerid, enteridx) { return 1; }
public OnEnterDone(playerid, enteridx) { return 1; }
public OnExitDone(playerid, enteridx) { return 1; }
static OnEnterStateSet(idx) {
  if (gEnter[idx][e_enType] == ENTER_TYPE_WHNOKNOWS) CreateEnter3DText(idx);

  want_save[idx] = true;
}

static LoadEnters() {
  mysql_tquery(DB_GetConnectionHandle(), "SELECT * FROM `enters`", "@__SetEntersState", "i", GetTickCount());
}

@__SetEntersState(loadStatrtTime);
@__SetEntersState(loadStatrtTime) {
  new
    pos_enter[64],
    pos_exit[64]
  ;

  cache_get_row_count(count);

  for (new i; i < count; i++) {
    cache_get_value_int(i, "ID", gEnter[i][e_enID]);
    cache_get_value(i, "Name", gEnter[i][e_enName]);
    cache_get_value(i, "Description", gEnter[i][e_enDesc]);
    cache_get_value(i, "EnterPos", pos_enter);
    cache_get_value(i, "ExitPos", pos_exit);
    DeserializeEnterExitPos(i, pos_enter, pos_exit);
    cache_get_value_int(i, "Type", gEnter[i][e_enType]);

    OnEnterStateSet(i);
  }

  gEntersIsLoaded = true;
  printf("Number of enters: %d, took %d ms ", count, GetTickCount() - loadStatrtTime);
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
    if (!want_save[i]) continue;

    want_save[i] = false;

    mysql_format(DB_GetConnectionHandle(),
      query, sizeof query,
      queryStr,
      gEnter[i][e_enName],
      gEnter[i][e_enDesc],
      gEnter[i][e_enID]
    );

    mysql_tquery(DB_GetConnectionHandle(), query);
  }
}

EntersAddOne(const name[], const pos_enter[], const pos_exit[], type = ENTER_TYPE_WHNOKNOWS) {
  static const 
    queryStr[] = "INSERT INTO `enters`\
    (`EnterPos`, `ExitPos`, `Type`, `Name`)\
    VALUES ('%e', '%e', %d, '%e')"
  ; // 128

  new query[128 + 64 + 64 + 32 + 144];

  mysql_format(DB_GetConnectionHandle(), query, sizeof query, queryStr, pos_enter, pos_exit, type, name);
  mysql_query(DB_GetConnectionHandle(), query);

  gEnter[count][e_enID] = cache_insert_id();

  DeserializeEnterExitPos(count, pos_enter, pos_exit);

  strcopy(gEnter[count][e_enName], name);

  OnEnterStateSet(count);

  count++;

  return cache_insert_id();
}

EntersDeleteOne(idx) {
  new query[36 + 11];

  mysql_format(DB_GetConnectionHandle(), query, sizeof query, "DELETE FROM `enters` WHERE `ID` = %d", gEnter[idx][e_enID]);
  mysql_query(DB_GetConnectionHandle(), query);
  
  if (IsValidDynamic3DTextLabel(gEnter[idx][e_enText3D])) {
    DestroyDynamic3DTextLabel(gEnter[idx][e_enText3D]);
  }

  memset(gEnter[idx]);
}

DeserializeEnterExitPos(idx, const pos_enter[], const pos_exit[] ) {
  sscanf(pos_enter, "p<|>fffii", 
    XYZ0(gEnter[idx][e_enPosEnter]),
    gEnter[idx][e_enPosEnterInt],
    gEnter[idx][e_enPosEnterWorld]
  );

  sscanf(pos_exit, "p<|>fffii", 
    XYZ0(gEnter[idx][e_enPosExit]),
    gEnter[idx][e_enPosExitInt],
    gEnter[idx][e_enPosExitWorld]
  );
}

hook function SetPlayerPos(playerid, Float:x, Float:y, Float:z) {
  new
    items[1],
    streamer_count = Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_OBJECT, items, sizeof(items), 300.0),
    freeze_time = (GetPlayerPing(playerid) * 4) + (streamer_count * 2) + 1550
  ;

  if (!GetPVarInt(playerid, "IsFrozen") && streamer_count) {
    TogglePlayerControllable(playerid, 0);
    SetTimerEx(!"@__UnFreezePlayer", freeze_time, false, !"d", playerid);
    SetPVarInt(playerid, "IsFrozen", 1);
  }

  continue(playerid, x, y, z + 0.3);
}

CMD:enter(playerid) {
  for (new i; i < count; i++) {
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, XYZ0(gEnter[i][e_enPosEnter]))) continue;
    if (gEnter[i][e_enPosEnterWorld] != GetPlayerVirtualWorld(playerid)) continue;
    if (gEnter[i][e_enPosEnterInt] != GetPlayerInterior(playerid)) continue;
    if (!OnEnterStart(playerid, i)) continue;

    SetPlayerPosEx(playerid, XYZ0(gEnter[i][e_enPosExit]), gEnter[i][e_enPosExitWorld], gEnter[i][e_enPosExitInt]);
    if (!isnull(gEnter[i][e_enDesc])) {
      SendClientMessage(playerid, COLOR_ACTIONS, "* %s", false, gEnter[i][e_enDesc]);
    }

    return OnEnterDone(playerid, i);
  }

  return 1;
}

CMD:exit(playerid) {
  for (new i; i < count; i++) {
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, XYZ0(gEnter[i][e_enPosExit]))) continue;
    if (gEnter[i][e_enPosExitWorld] != GetPlayerVirtualWorld(playerid)) continue;
    if (gEnter[i][e_enPosExitInt] != GetPlayerInterior(playerid)) continue;
    if (!OnExitStart(playerid, i)) continue;

    SetPlayerPosEx(playerid, XYZ0(gEnter[i][e_enPosEnter]), gEnter[i][e_enPosEnterWorld], gEnter[i][e_enPosEnterInt]);

    return OnExitDone(playerid, i);
  }

  return 1;
}

static CreateEnter3DText(idx) {
  if (gEnter[idx][e_enText3D]) {
    DestroyDynamic3DTextLabel(gEnter[idx][e_enText3D]);
  }

  format( gString, sizeof gString,cWHITE"%s\n"cBLUE"[Press Y]", gEnter[idx][e_enName]);
  gEnter[idx][e_enText3D] = CreateDynamic3DTextLabel(
    gString,
    COLOR_BLUE,
    XYZ0(gEnter[idx][e_enPosEnter]), 4.0, 
    INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 
    gEnter[idx][e_enPosEnterWorld], gEnter[idx][e_enPosEnterInt]
  );
}

@__UnFreezePlayer(playerid);
@__UnFreezePlayer(playerid) {
  SetPVarInt(playerid, "IsFrozen", 0);
  TogglePlayerControllable(playerid, 1);
}

stock GetEntersCount() {
  return count;
}

stock GetEnterIndex(enterid) {
  for (new i; i < count; i++) {
    if (gEnter[i][e_enID] != enterid) continue;

    return i;
  }

  return -1;
}

stock SetEnterName(enterid, const newname[]) {
  new idx = GetEnterIndex(enterid);

  if (idx < 0) return;

  strcopy(gEnter[idx][e_enName], newname);

  OnEnerStateSet(idx);
}
