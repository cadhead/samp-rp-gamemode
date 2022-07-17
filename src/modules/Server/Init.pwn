public OnGameModeInit() {
  SendRconCommand("password 3ff8f305a9c023943246d85e36c68ae1bdb2261330ed8d60065effed57d91c83");

  // Streamer config
  Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, OBJECT_STREAM_LIMIT, -1);
  Streamer_SetVisibleItems(STREAMER_TYPE_PICKUP, 3900, -1);
  Streamer_SetVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL, 1000, -1);
  print("> Streamer Configuration Complete.");

  // SA-MP gamemode settings
  ShowNameTags(true);
  SetNameTagDrawDistance(15.0);
  AllowInteriorWeapons(true);
  DisableInteriorEnterExits();
  EnableStuntBonusForAll(false);
  ShowPlayerMarkers(false);
  ManualVehicleEngineAndLights();
  EnableVehicleFriendlyFire();
  // SetVehiclePassengerDamage(true);
  // SetDisableSyncBugs(true);
  // SetDamageFeed(false);
  SetMaxConnections(3, e_FLOOD_ACTION_GHOST);
  SendRconCommand("cookielogging 0");
  SendRconCommand("messageholelimit 9000");
  SendRconCommand("ackslimit 11000");
  print("> GameMode Settings Loaded.");

  // Server Informations
  new
    str[64];

  format(str, sizeof(str), "hostname %s", HOSTNAME);
  SendRconCommand(str);
  SetGameModeText(SCRIPT_VERSION);
  print("> Server Info Loaded.");

  GMX_Set(2);

  CountSeconds_Set(SERVER_UNLOCK_TIME);

  printf("> GameMode Time Set on %s", 
    ReturnTime(),
    SERVER_NAME
  );
}