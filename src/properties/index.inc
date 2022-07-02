#if defined _properites_included
  #endinput
#endif

#define _properites_included

#include "./properties/interiors"

#include <YSI_Coding\y_hooks>

#define MAX_PROPERTIES MAX_ENTERS

enum e_Property {
  e_prID,
  e_prEnterID,
  e_prOwnerID,
  e_prFactionID,
  e_prPrice,
  e_prCash,
  e_prInvItems[256],
  e_prInvItemsCount[256],
  bool:e_prLocked
}

new gProperty[MAX_PROPERTIES][e_Property];
new bool:gPropertiesIsLoaded = false;

static count = 0;
static bool:want_save[MAX_PROPERTIES] = false;

hook OnGameModeInit() {
  LoadProperties();

  return 1;
}

hook OnGameModeExit() {
  SaveProperties();

  return 1;
}

hook function OnEnterStart(playerid, enteridx) { 
  for (new i; i < count; i++) {
    if (GetEnterID(enteridx) != gProperty[i][e_prEnterID]) continue;
    if (gProperty[i][e_prLocked]) {
      GameTextForPlayer(playerid, "~r~LOCKED", 3000, 1);

      return 0;
    }
  }

  return continue(playerid, enteridx);
}

static LoadProperties() {
  mysql_tquery(DB_GetConnectionHandle(), "SELECT * FROM `properties`", "@__SetPropertiesState", "d", GetTickCount());
}

static SaveProperties() {
  static const queryStr[] = "UPDATE `properties`\
    SET `OwnerID` = '%d',\
    `FactionID` = '%d',\
    `Price` = '%d',\
    `Cash` = '%d',\
    `InventoryItems` = '%e',\
    `InventoryItemsCount` = '%e',\
    `Locked` = '%d'\
    WHERE `ID` = '%d'"
  ; // 199

  new query[199 + 256 + 256 + (10 * 5)];

  for (new i; i < count; i++) {
    mysql_format(DB_GetConnectionHandle(),
      query, sizeof query, queryStr,
      gProperty[i][e_prOwnerID],
      gProperty[i][e_prFactionID],
      gProperty[i][e_prPrice],
      gProperty[i][e_prCash],
      gProperty[i][e_prInvItems],
      gProperty[i][e_prInvItemsCount],
      gProperty[i][e_prLocked],
      gProperty[i][e_prID]
    );
    mysql_query(DB_GetConnectionHandle(), query);
  }
}

PropertiesAddOne(enterid) {
  static const queryStr[] = "INSERT INTO `properties` (`EnterID`) VALUES ('%d')";

  new query[122 + (5 * 10)];

  gProperty[count][e_prEnterID] = enterid;

  mysql_format(DB_GetConnectionHandle(),
    query, sizeof query, queryStr,
    gProperty[count][e_prEnterID]
  );

  mysql_query(DB_GetConnectionHandle(), query);

  count++;

  return cache_insert_id();
}

PropertiesDeleteOne(idx) {
  new query[40 + 11];

  mysql_format(DB_GetConnectionHandle(), query, sizeof query, "DELETE FROM `properties` WHERE `ID` = %d", gProperty[idx][e_prID]);
  mysql_query(DB_GetConnectionHandle(), query);

  MemSet(gProperty[idx]);
}

PropertySetPickUp(idx, enterid) {
  new
    e_index = GetEnterIndex(enterid),
    e_owner = gProperty[idx][e_prOwnerID],
    house_pickup = e_owner ? 1273 : 1272,
    bussiness_pickup = 1239;

  if (GetEnterType(e_index) == ENTER_TYPE_HOUSE)
    CreateEnterPickUp(e_index, house_pickup);
  if (GetEnterType(e_index) == ENTER_TYPE_BUSSINESS)
    CreateEnterPickUp(e_index, bussiness_pickup);
}

@__SetPropertiesState(loadStatrtTime);
@__SetPropertiesState(loadStatrtTime) {
  cache_get_row_count(count);

  for (new i; i < count; i++) {
    cache_get_value_int(i, "ID", gProperty[i][e_prID]);
    cache_get_value_int(i, "EnterID", gProperty[i][e_prEnterID]);
    cache_get_value_int(i, "OwnerID", gProperty[i][e_prOwnerID]);
    cache_get_value_int(i, "FactionID", gProperty[i][e_prFactionID]);
    cache_get_value_int(i, "Price", gProperty[i][e_prPrice]);
    cache_get_value_int(i, "Cash", gProperty[i][e_prCash]);
    cache_get_value(i, "InventoryItems", gProperty[i][e_prInvItems]);
    cache_get_value(i, "InventoryItemsCount", gProperty[i][e_prInvItemsCount]);
    cache_get_value_int(i, "Locked", gProperty[i][e_prLocked]);

    PropertySetPickUp(i, gProperty[i][e_prEnterID]);
  }

  gPropertiesIsLoaded = true;
  printf("Number of properties: %d, took %d ms ", count, GetTickCount() - loadStatrtTime);

  return 1;
}
