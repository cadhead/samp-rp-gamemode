// Account
enum e_Account {
  e_acID,
  e_acName[MAX_PLAYER_NAME + 1],
  e_acPasswdHash[MAX_PASSWDHASH + 1],
  e_acPasswdSalt[MAX_PASSWDSALT + 1],
  e_acEmail[64],
  e_acWarns,
  bool:e_acBanned,
  e_acConnTime,
  e_acLastLogin,
  e_acAdmin,
  e_acPremium
}
new gAccount[MAX_PLAYERS][e_Account];

// Character
enum e_Character {
  e_cName[MAX_PLAYER_NAME + 1],
  e_cCash,
  e_cSkin,
  Float:e_cSpawn[4],
  e_cSpawnInt,
  e_cSpawnWorld,
  e_cSex,
  e_cDeathStage
}
new gCharacter[MAX_PLAYERS][e_Character];

// Death system
enum {
  CHARACTER_HEALTHY = 0,
  CHARACTER_INJURED,
  CHARACTER_DIED
}
enum e_Character_Death {
  e_dAmount,
  e_dWeapon,
  e_dWhen,
  e_dBodyPart,
  e_dBy
}

// Enters
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
  STREAMER_TAG_PICKUP:e_enPickUp
}

new gEnter[MAX_ENTERS][e_Enters];

// Properties
enum e_Property {
  e_prID,
  e_prEnterID,
  e_prOwnerID,
  e_prOwnerName[MAX_PLAYER_NAME],
  e_prFactionID,
  e_prPrice,
  e_prCash,
  e_prInvItems[256],
  e_prInvItemsCount[256],
  e_prType,
  bool:e_prLocked
}
enum {
  ENTER_TYPE_WHNOKNOWS = 0,
  ENTER_TYPE_BUSSINESS,
  ENTER_TYPE_HOUSE
}
new gProperty[MAX_PROPERTIES][e_Property];

// Factions
enum e_Faction {
  e_fID,
  e_fName,
  e_fType,
  e_fRanks[MAX_FACTION_RANKS]
}
new gFaction[MAX_FACTIONS][e_Faction];

// Helpers
enum {
  DURATION_SECOND = 1,
  DURATION_MINUTE = 60 * DURATION_SECOND,
  DURATION_HOUR   = 60 * DURATION_MINUTE,
  DURATION_DAY    = 24 * DURATION_HOUR,
  DURATION_WEEK   = 7 * DURATION_DAY,
  DURATION_MONTH  = 30 * DURATION_DAY,
  DURATION_YEAR   = 365 * DURATION_DAY,
  
  DURATION_PERMANENT = 0,
  DURATION_EXPIRED   = -1
};
