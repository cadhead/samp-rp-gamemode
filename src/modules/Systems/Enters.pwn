#include <YSI_Coding\y_hooks>

static
  Iterator: Enter<MAX_ENTERS>;

#define __enters_GetEnterPos(%1) XYZ0(gEnter[%1][e_enPosEnter]),gEnter[%1][e_enPosEnterInt],gEnter[%1][e_enPosEnterWorld]
#define __enters_GetExitPos(%1) XYZ0(gEnter[%1][e_enPosExit]),gEnter[%1][e_enPosExitInt],gEnter[%1][e_enPosExitWorld]

static EntersLoad() {
  Iter_Init(Enter);
  
  inline SetEntersState() {
    new
      count = cache_num_rows(),
      pos_enter[64],
      pos_exit[64];

    if (!count) return print("> No enters exist to load in db.");

    for (new i; i < count; i++) {
      cache_get_value_int(i, "ID", gEnter[i][e_enID]);
      cache_get_value(i, "Name", gEnter[i][e_enName]);
      cache_get_value(i, "Description", gEnter[i][e_enDesc]);
      cache_get_value(i, "EnterPos", pos_enter);
      cache_get_value(i, "ExitPos", pos_exit);
      DeserializePosition(pos_enter, __enters_GetEnterPos(i));
      DeserializePosition(pos_exit, __enters_GetExitPos(i));
      cache_get_value_int(i, "Type", gEnter[i][e_enType]);

      Iter_Add(Enter, i);
    }

    printf("> Enters Loaded. [%d/%d]", Iter_Count(Enter), MAX_ENTERS);

    return 1;
  }

  MySQL_TQueryInline(SQL_GetHandle(), using inline SetEntersState,
    va_fquery(SQL_GetHandle(), "SELECT * FROM enters WHERE 1"), "");

  return 1;
}

// Commands

CMD:enter(playerid) {
  foreach (new enter_key : Enter) {
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, XYZ0(gEnter[enter_key][e_enPosEnter]))) continue;
    if (gEnter[enter_key][e_enPosEnterWorld] != GetPlayerVirtualWorld(playerid)) continue;
    if (gEnter[enter_key][e_enPosEnterInt] != GetPlayerInterior(playerid)) continue;
    if (!OnEnterStart(playerid, enter_key)) continue;

    SetPlayerPos(playerid, XYZ0(gEnter[enter_key][e_enPosExit]));
    SetPlayerVirtualWorld(playerid, gEnter[enter_key][e_enPosExitWorld]);
    SetPlayerInterior(playerid, gEnter[enter_key][e_enPosExitInt]);

    if (!isnull(gEnter[enter_key][e_enDesc])) {
      va_SendClientMessage(playerid, COLOR_ACTIONS, "* %s", gEnter[enter_key][e_enDesc]);
    }

    return OnEnterDone(playerid, enter_key);
  }

  return 1;
}

CMD:exit(playerid) {
  foreach (new enter_key : Enter) {
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, XYZ0(gEnter[enter_key][e_enPosExit]))) continue;
    if (gEnter[enter_key][e_enPosExitWorld] != GetPlayerVirtualWorld(playerid)) continue;
    if (gEnter[enter_key][e_enPosExitInt] != GetPlayerInterior(playerid)) continue;
    if (!OnExitStart(playerid, enter_key)) continue;

    SetPlayerPos(playerid, XYZ0(gEnter[enter_key][e_enPosEnter]));
    SetPlayerVirtualWorld(playerid, gEnter[enter_key][e_enPosEnterWorld]);
    SetPlayerInterior(playerid, gEnter[enter_key][e_enPosEnterInt]);

    return OnExitDone(playerid, enter_key);
  }

  return 1;
}

// API

EntersGetCount() {
  return Iter_Count(Enter);
}

EntersAddOne(const name[], const pos_enter[], const pos_exit[], type = ENTER_TYPE_WHNOKNOWS) {
  inline SetEnterState() {
    new
      idx = Iter_Free(Enter);

    gEnter[idx][e_enID] = cache_insert_id();
    strcopy(gEnter[idx][e_enName], name);
    gEnter[idx][e_enType] = type;

    DeserializePosition(pos_enter, __enters_GetEnterPos(idx));
    DeserializePosition(pos_exit, __enters_GetExitPos(idx));
    if (gEnter[idx][e_enPosEnterInt] > 0) {
      gEnter[idx][e_enPosEnterWorld] = gEnter[idx][e_enID];
    }

    Iter_Add(Enter, idx);

    EntersChangeEnterPickup(gEnter[idx][e_enID]);

    return 1;
  }

  mysql_tquery(SQL_GetHandle(), "START TRANSACTION");
  MySQL_TQueryInline(SQL_GetHandle(), using inline SetEnterState,
    va_fquery(SQL_GetHandle(),
      "INSERT INTO `enters`\
      (`EnterPos`, `ExitPos`, `Type`, `Name`)\
      VALUES ('%e', '%e', %d, '%e')",
      pos_enter, pos_exit, type, name
    )
  );
  mysql_tquery(SQL_GetHandle(), "COMMIT");

  return 1;
}

EntersDeleteOne(id);

EntersChangeEnterPickup(id, pickupid = -1) {
  if (pickupid == -1) return;

  foreach (new key : Enter) {
    if (gEnter[key][e_enID] == id) {
      DestroyDynamicPickup(gEnter[key][e_enPickUp]);
      gEnter[key][e_enPickUp] = CreateDynamicPickup(pickupid, 2,
        XYZ0(gEnter[key][e_enPosEnter]),
        gEnter[key][e_enPosEnterWorld],
        gEnter[key][e_enPosEnterInt]
      );

      return;
    }
  }
}

hook OnGameModeInit() {
  EntersLoad();
}

hook function SetPlayerPos(playerid, Float:x, Float:y, Float:z) {
  new
    items[1],
    streamer_count = Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_OBJECT, items, sizeof(items), 300.0),
    freeze_time = (GetPlayerPing(playerid) * 4) + (streamer_count * 2) + 1550
  ;

  inline unfreeze() {
    TogglePlayerControllable(playerid, true);
  }

  if (!GetPVarInt(playerid, "IsFrozen") && streamer_count) {
    TogglePlayerControllable(playerid, false);
    SetPVarInt(playerid, "IsFrozen", 1);
    Timer_CreateCallback(using inline unfreeze, freeze_time, 1);
  }

  continue(playerid, x, y, z + 0.3);
}
